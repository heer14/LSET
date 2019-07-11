// OffLineSDKtest.cpp : Defines the entry point for the console application.
//

#ifdef WIN32
#include "stdafx.h"
#endif
#include <stdint.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <assert.h>
#include <chrono>
#include <algorithm>
#include <functional>
#include <float.h>
#include <numeric>

#ifndef _WIN32
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sendfile.h>
#include <unistd.h>
#else
#define NOMINMAX //Prevent to definition min and max in Windows.h
#include <Windows.h>
#define snprintf _snprintf_s
#undef LoadImage 
#endif
#include "OfflineFilterSDKHigh.h"
#pragma comment(lib,"OfflineFilterSDK_High.lib")

#define MAX_FRAMECOUNT	(4096)

const uint32_t REGRESSION_TEST_TOLERANCE_PIXEL_WISE_DIFF =  1;  // if pixel wise difference is larger than this, it would be counted as a different pixel
const uint32_t REGRESSION_TEST_TOLERANCE_DIFF_PIXELS     = 32;  // if the number of different pixels are larger than this, regression test fail

using namespace offline;

bool operator == (Point3Df_t L, Point3Df_t R);
bool checkArray(uint16_t *expect, uint16_t *actual, int sz);
void assertArray(uint16_t *expect, uint16_t *actual, int sz);
void setup(std::vector<uint16_t> &inDepth, std::vector<uint16_t> &inIR, const char *paramDir, const char *path_3D, const char *path_2D, enum APVersion version = APVersion::LATEST);
int LoadTestFiles(const char* test_dir, std::vector<std::string> &inputs2D, std::vector<std::string> &inputs3D, std::vector<std::string> &results2D, std::vector<std::string> &results3D);

void testPreprocessing_core_PL(char *test_dir, enum APVersion version, FlipKind kFlip = FLIP_NORMAL, int nIgnoreFirstFrame = 2, uint32_t nTolerancePixelDiff = REGRESSION_TEST_TOLERANCE_PIXEL_WISE_DIFF, uint32_t nToleranceDiffCount = REGRESSION_TEST_TOLERANCE_DIFF_PIXELS);
void GetFilteredPointCloudPatchHelper(std::vector<Point3Df_t> &out, std::string calibration_dir, std::string imageOA, std::string imageOR, int patch[4], FlipKind kFilp = FLIP_NORMAL);

static void GetStats(uint16_t *img, int len, double *mean, double *variance);

const int N_VGA_PIXELS = 640 * 480;
const int N_QVGA_PIXELS = 320 * 240;
const int N_VGA_BYTES = N_VGA_PIXELS * 2;
const int N_QVGA_BYTES = N_QVGA_PIXELS * 2;
const float64_t THREED_LU_FLT_EPSION = (0.001f);

static void assertInvalidResult(ErrorType ret, const std::vector<Point3Df_t> actual, int len);

int Example0_CalibrationFille_Format_Updated()
{
	// Old version's calibration format might fail to load
	//assert(OMS_FAIL == offline::InitializePreProcessing_core("./params/B0", nullptr));

	// New version (= 100) format
	assert(SUCCESS == offline::InitializePreProcessing_core("./params/C1/", nullptr));

	// C0-R2 version
	assert(SUCCESS == offline::InitializePreProcessing_core("./params/C0-R2/", nullptr));

	return 0;
}

int Example0_1_InitializingFromEEPROMFormat()
{
	int nCameras = 2;
	int ret = offline::InitializePreProcessing_core("./TestFiles/eeprom/", nCameras);
	assert (SUCCESS == ret);

	PreprocessorParams *param = offline::GetCameraParam(eCameraPosition::FrontRight);
	float64_t expect_c3 = 0.000000011609;
	int32_t actual_coef_cube = param->coef_cube; // 829
	float64_t t = 31.273438;
	float64_t a1 = -0.000000129690;
	float64_t b1 = 0.000018932591;
	float64_t c1 = -0.000881916145;
	float64_t a = 1.f - ((((a1 * t + b1) * t) + c1) * t);
	float64_t TCA_cube = expect_c3 * (a * a * a);
	int32_t expect_coef_cube = static_cast<int32_t>(TCA_cube * pow(2.0f, 36) + 0.5f);

	/*
	OMS CALIB DEBUG> TCModel - Model coef[0]: 0.000362704741
	OMS CALIB DEBUG> TCModel - Model coef[1]: -0.050312358886
	OMS CALIB DEBUG> TCModel - Model coef[2]: 4.017939567566
	OMS CALIB DEBUG> TCModel - Model coef[3]: -0.000000129690
	OMS CALIB DEBUG> TCModel - Model coef[4]: 0.000018932591
	OMS CALIB DEBUG> TCModel - Model coef[5]: -0.000881916145
	*/
	// TCA_cube  = c3 * (a * a * a);
	//  where c3 = cube
	//         a = 1 - ((((a1 * t + b1) * t) + c1) * t)
	//         t = temperature
	//        a1 = TCModel_Depth[3]
	//        b1 = TCModel_Depth[4]
	//        c1 = TCModel_Depth[5]
	// coef_cube = (int32) TCA_cube * 2.0^36 + 0.5f
	assert (expect_coef_cube == actual_coef_cube);
	return 0;
}
/*
 * APIs for Preprocessing on PS
 *		1. offline::Preprocessing_core_PS
 *		2. offline::GetPointCloudArray_3d
 */
int Example1_preprocessing_core_PS()
{
	std::vector<uint16_t> pusInDepth(640 * 480);
	std::vector<uint16_t> pusOutDepth(640 * 480);
	std::vector<uint16_t> pusInIR(640 * 480);
	std::vector<uint16_t> pusResizeIR(320 * 240);

	char* IRImage_In = "./TestFiles/B0_Beta/LG_OA_00001.png";
	char* DepthImage_In = "./TestFiles/B0_Beta/LG_OR_00001.png";
	char* DepthImage_Out = "./TestFiles/B0_Beta/LG_OR_pre_00001.raw";

	ErrorType ret = offline::InitializePreProcessing_core("./params/C1/", nullptr);
	assert (SUCCESS == ret);

	assert (0 == offline::LoadPNG(DepthImage_In, (char*)&pusInDepth[0], 640*480*2));
	assert (0 == offline::LoadPNG(IRImage_In, (char*)&pusInIR[0], 640*480*2));

	ret = offline::Preprocessing_core_PS(&pusInDepth[0], &pusOutDepth[0], &pusInIR[0]);

	assert (SUCCESS == ret);

	offline::SaveRaw(DepthImage_Out, (char*)&pusOutDepth[0], 640*480*2);
	return 0;
}

int Example2_GetPointCloudArray_3d()
{
	bool bPrintWorldPoints = true;
	int wd = 640;
	int ht = 480;

	ErrorType ret = offline::InitializePreProcessing_core("./params/C1/", nullptr);
	assert (SUCCESS == ret);

	std::vector<uint16_t> pusInDepth(wd * ht);
	std::vector<uint16_t> pusOutDepth(wd * ht);
	std::vector<uint16_t> pusInIR(wd * ht);

 	assert (0 == offline::LoadRaw("./TestFiles/C1/OR.raw", (char*)&pusInDepth[0], wd * ht * 2));
	assert (0 == offline::LoadRaw("./TestFiles/C1/OA.raw", (char*)&pusInIR[0], wd * ht * 2));

	ret = Preprocessing_core_PS(&pusInDepth[0], &pusOutDepth[0], &pusInIR[0]);
	assert (SUCCESS == ret);

	assert (0 == offline::SaveRaw("./TestFiles/C1/Ex2_OR_result.raw", (char*)&pusOutDepth[0], wd * ht * 2));

	std::vector<Point3Du_t> arImagePoint;	// in
	std::vector<Point3Df_t> arWorldPoint;	// out

	float pfRT[12] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 };
	uint16_t u = 345;
	uint16_t v = 264;
	uint16_t r = pusOutDepth[v * wd + u];
	int iCameraIndex = 0;

	arImagePoint.push_back({u, v, r});

	printf ("u:%d, v:%d, r:%d\n", u, v, r);
	ret = offline::GetPointCloudArray_3d(&arImagePoint, &arWorldPoint, pfRT, wd, ht, 0, 2000, iCameraIndex);

	assert(SUCCESS == ret);

	if (bPrintWorldPoints)
	{
		for (auto p : arWorldPoint)
		{
			printf ("x:%f, y:%f, z:%f\n", p.x, p.y, p.z);
		}
	}

	return 0;
}

int Example2_2_GetPointCloudArray_3d()
{
	int wd = 320;
	int ht = 240;
	float pfRT[12] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 };
	std::vector<Point3Du_t> inputs;
	std::vector<Point3Df_t> actual;
	std::vector<Point3Df_t> expect;
	int iCameraIndex = 0;

	ErrorType ret = offline::InitializePreProcessing_core("./TestFiles/3d-lookup/", nullptr);
	assert (SUCCESS == ret);

	// from R10.2.0.0
	inputs.push_back({160, 120, 1316});
	inputs.push_back({160, 120, 179} );
	inputs.push_back({160, 120, 333} );
	expect.push_back({-0.022f, -0.005f, 1.316f});
	expect.push_back({-0.003f, -0.001f, 0.179f});
	expect.push_back({-0.006f, -0.001f, 0.333f});

	// from R10.4.2.0
	inputs.push_back({160,120,1185});
	inputs.push_back({160,120,275});
	inputs.push_back({160,120,306});
	expect.push_back({-0.020f, -0.004f, 1.185f});
	expect.push_back({-0.005f, -0.001f, 0.275f});
	expect.push_back({-0.005f, -0.001f, 0.306f});

	ret = offline::GetPointCloudArray_3d(&inputs, &actual, pfRT, wd, ht, 0, 2000, iCameraIndex);
	assert(SUCCESS == ret);

	for (int i = 0; i < actual.size(); i++)
	{
		uint16_t u = inputs[i].u;
		uint16_t v = inputs[i].v;
		uint16_t r = inputs[i].r;
		Point3Df_t a = actual[i];
		Point3Df_t e = expect[i];
		printf ("(u:%d, v:%d, r:%04d) -> (actual, expect): {x:(%.3f, %.3f), y:(%.3f, %.3f), z:(%.3f, %.3f)}\n",
			u, v, r, a.x, e.x, a.y, e.y, a.z, e.z);
		assert (a == e);
	}

	return 0;
}

bool operator == (Point3Df_t L, Point3Df_t R)
{
	return (fabs(L.x - R.x) < THREED_LU_FLT_EPSION) &&
		   (fabs(L.y - R.y) < THREED_LU_FLT_EPSION) &&
		   (fabs(L.z - R.z) < THREED_LU_FLT_EPSION);
}

/*
 * END of APIs for Preprocessing on PS
 */


/*
 * APIs for Preprocessing on PL
 *		1. offline::Preprocessing_core_PL
 *		2. offline::GetFilteredPointCloudPatch
 */
int Example3_Preprocessing_core_PL()
{
	ErrorType ret = offline::InitializePreProcessing_core("./params/C1/", nullptr);
	assert (SUCCESS == ret);

	std::vector<uint16_t> pusInDepth(640 * 480);
	std::vector<uint16_t> pusOutDepth(320 * 240);
	std::vector<uint16_t> pusInIR(640 * 480);
	std::vector<uint16_t> pusResizeIR(320 * 240);

	assert (0 == offline::LoadRaw("./TestFiles/C1/OR.raw", (char*)&pusInDepth[0], 640*480*2));
	assert (0 == offline::LoadRaw("./TestFiles/C1/OA.raw", (char*)&pusInIR[0], 640*480*2));

	// input: VGA image frame
	assert(SUCCESS == offline::Preprocessing_core_PL(&pusInDepth[0], &pusOutDepth[0], &pusInIR[0], &pusResizeIR[0]));
	// result: QVGA image frame

	offline::SaveRaw("./TestFiles/C1/Ex3_OR_result.raw", (char*)&pusOutDepth[0], 320 * 240 * 2);

	return 0;
}

/*
* APIs for Preprocessing on PL QVGA
*		1. offline::Preprocessing_core_PL
*/
int Example3_1_Preprocessing_core_PL_VGA()
{
	ErrorType ret = offline::InitializePreProcessing_core("./params/C1/", nullptr);
	assert(SUCCESS == ret);

	std::vector<uint16_t> pusInDepth(640 * 480);
	std::vector<uint16_t> pusOutDepth(640 * 480);
	std::vector<uint16_t> pusInIR(640 * 480);
	std::vector<uint16_t> pusResizeIR(640 * 480);

	assert(0 == offline::LoadRaw("./TestFiles/C1/OR.raw", (char*)&pusInDepth[0], 640 * 480 * 2));
	assert(0 == offline::LoadRaw("./TestFiles/C1/OA.raw", (char*)&pusInIR[0], 640 * 480 * 2));

	// input: VGA image frame
	assert(SUCCESS == offline::Preprocessing_core_PL_VGA(&pusInDepth[0], &pusOutDepth[0], &pusInIR[0], &pusResizeIR[0]));
	// result: QVGA image frame

	offline::SaveRaw("./TestFiles/C1/Ex3_OR_VGA_result.raw", (char*)&pusOutDepth[0], 640 * 480 * 2);

	return 0;
}


int Example3_2_Preprocessing_core_PL_Flip()
{
	ErrorType ret = offline::InitializePreProcessing_core("./params/C1/", nullptr);
	assert (SUCCESS == ret);

	std::vector<uint16_t> pusInDepth(640 * 480);
	std::vector<uint16_t> pusOutDepth(320 * 240);
	std::vector<uint16_t> pusInIR(640 * 480);
	std::vector<uint16_t> pusResizeIR(320 * 240);

	assert (0 == offline::LoadRaw("./TestFiles/C1/OR.raw", (char*)&pusInDepth[0], 640*480*2));
	assert (0 == offline::LoadRaw("./TestFiles/C1/OA.raw", (char*)&pusInIR[0], 640*480*2));

	// input: VGA image frame
	assert(SUCCESS == offline::Preprocessing_core_PL(&pusInDepth[0], &pusOutDepth[0], &pusInIR[0], &pusResizeIR[0]));
	// result: QVGA image frame

	offline::SaveRaw("./TestFiles/C1/Ex3_OR_result.raw", (char*)&pusOutDepth[0], 320 * 240 * 2);
	return 0;
}

int Example4_GetFilteredPointCloudPatch()
{
	const char *imageOR = "./TestFiles/C1/OR.raw";
	const char *imageOA = "./TestFiles/C1/OA.raw";
	int p[4] =  {240/2/*patch_y*/, 320/2/*patch_x*/, 12/*patch size*/, 12/*patch size*/};
	std::vector<Point3Df_t> arWorldPoint;

	GetFilteredPointCloudPatchHelper(arWorldPoint,    "./params/C1/", imageOR, imageOA, p);
	return 0;
}

int Example4_2_GetFilteredPointCloudPatch_Filp()
{
	/*
	 * for givne any patch P and image I, world coordinate (x,y,z) should be same
	 * GetFilteredPointCloudPatch(P, I) == GetFilteredPointCloudPatch(P', I')
	 *      where I' = flip(I), P' = flip(P)
	 */
	bool bPrintWorldPoints = false;
	std::string imageIR("./TestFiles/flip/OA.raw");
	std::string imageDP("./TestFiles/flip/OR.raw");

	int nCameras = 1;
	std::vector<Point3Df_t> expect;
	std::vector<Point3Df_t> actual[3];

	// e.g) vertical flip case, 8x8 patch:[(60, 60) ~ (67, 67)] -> flipped 8x8 patch: (60, 173) ~ (67, 180)]
	// Below is the y index change when flipped
	// 0   ->   0
	// 1   -> 239
	// 2   -> 238
	// ..  ->  ..
	// 239 ->   1

	int p1[4] = { 60/*patch_y*/,                60/*patch_x*/, 16/*patch_width*/, 16/*patch_height*/};
	int p2[4] = { 239-60-15+1/*patch_y*/,       60/*patch_x*/, 16/*patch_width*/, 16/*patch_height*/}; // UP-DOWN FLIPPED patch

	GetFilteredPointCloudPatchHelper(expect,    "./TestFiles/flip/", imageIR, imageDP, p1, FLIP_NORMAL);
	GetFilteredPointCloudPatchHelper(actual[0], "./TestFiles/flip/", imageIR, imageDP, p2, FLIP_VERTICAL);

	auto diffsum = [&] (std::vector<Point3Df_t> expect, std::vector<Point3Df_t> actual) {
		float32_t ret = 0.f;
		for (int i = 0; i < expect.size(); i++)
		{
			 ret += (expect[i].y - actual[i].y);
			 //std::cout << ret << " " << expect[i].y << " " << actual[i].y << std::endl;

		}
		return ret;
	};
	//printf ("sum of difference = %f\n", diffsum(expect, actual[0]));
	assert (diffsum(expect, actual[0]) < 0.00001);

	return 0;
}

int Example4_2_GetFilteredPointCloudPatch_Filp_MinModel()
{
	typedef struct {
		int32_t y;
		int32_t x;
		int32_t ht;
		int32_t wd;
	} ROI;

	ErrorType ret;
	std::vector<uint16_t> DP_out(N_VGA_PIXELS);
	std::vector<uint16_t> IR_out(N_VGA_PIXELS);

	std::vector<Point3Df_t> w1;
	std::vector<Point3Df_t> w2;
	float pfRT[12] = {
		0.998380, -0.023524,-0.051798, 1.151155,  
		-0.020392,-0.997978, 0.060195, -0.035638,  
		-0.053109,-0.059041,-0.996842, 1.218826};
	int idx = 0;
	ROI p1 = {240, 160,       1, 1}; // y, x, height, width of patch
	ROI p2 = {240, 639 - 160, 1, 1}; // x reflects horizontal flip

	std::string dir = "TestFiles/max-5.0-tpr-comp/";
	// initialize for OMS-MIN two cameras
	auto m_p = offline::InitializePreProcessing_core((char*)dir.c_str(), 2);

	// put arbitrary depth values
	uint16_t d = 500;
	uint16_t ir = 1000;
	std::fill(DP_out.begin(), DP_out.end(), d);
	std::fill(IR_out.begin(), IR_out.end(), ir);

	// by default, it is set to LHD
	assert (false == offline::IsRHD());

	// LHD
	offline::SetRHD(false);
	assert (false == offline::IsRHD());

	ret = offline::GetFilteredPointCloudPatch(DP_out.data(), IR_out.data(), &w1, p1.y, p1.x, p1.ht, p1.wd, pfRT, eCameraPosition::FrontRight);
	assertInvalidResult (ret, w1, p1.wd * p1.ht);

	// RHD: expecting is horizontal flipped 
	offline::SetRHD(true);
	assert (true == offline::IsRHD());

	ret = offline::GetFilteredPointCloudPatch(DP_out.data(), IR_out.data(), &w2, p2.y, p2.x, p2.ht, p2.wd, pfRT, eCameraPosition::FrontRight);
	assertInvalidResult (ret, w1, p1.wd * p1.ht);

	float x_diff = abs(w1[0].x - w2[0].x);
	float y_diff = abs(w1[0].y - w2[0].y);
	float z_diff = abs(w1[0].z - w2[0].z);
	assert (x_diff < 0.0001f);
	assert (y_diff < 0.0001f);
	assert (z_diff < 0.0001f);
	return 0;
}

int Example4_3_PointFilter()
{
	char outfile[2048];
	std::vector<uint16_t> DP_RAW(640 * 480);
	std::vector<uint16_t> IR_RAW(640 * 480);
	std::vector<uint16_t> DP(320 * 240);
	std::vector<uint16_t> IR(320 * 240);

	std::vector<Point3Du_t> validPoints;
	std::vector<Point3Du_t> invalidPoints(1);
	uint16_t patch_wd = 8;
	uint16_t patch_ht = 8;
	double mean0, mean1;
	double variance0, variance1;
	std::vector<uint16_t> rs;
	std::string dir = "TestFiles/pointfilter/";

	offline::LoadRaw(dir + "DP.in.raw", (char*)DP_RAW.data(), 640 * 480 * 2);
	offline::LoadRaw(dir + "IR.in.raw", (char*)IR_RAW.data(), 640 * 480 * 2);

	ErrorType r = offline::InitializePreProcessing_core((char*)dir.c_str());
	assert (r == SUCCESS);

	int ret = offline::Preprocessing_core_PL(DP_RAW.data(), DP.data(), IR_RAW.data(), IR.data());
	assert (ret == 0);

	offline::SaveRaw(dir + "DP.raw", (char*)DP.data(), 320 * 240 * 2);
	offline::SaveRaw(dir + "IR.raw", (char*)IR.data(), 320 * 240 * 2);

	// case 1. valid input
	for (uint16_t y = patch_ht; y < (239 - patch_ht); y++)
	{
		for (uint16_t x = patch_wd; x < (319 - patch_wd); x++)
		{
			// push {u,v,r}. r is don't care value for PointFilter
			validPoints.push_back({x, y, 0});
		}
	}
	
	rs = offline::PointFilter(DP.data(), IR.data(), validPoints, patch_ht, patch_wd, 0);
	snprintf(outfile, 2048, "%sDP.filtered.%dx%d.raw", dir.c_str(), 319 - (2*patch_wd), 239 - (2*patch_ht));
	offline::SaveRaw(outfile, (char*)rs.data(), rs.size() * 2);


	GetStats(DP.data(), DP.size(), &mean0, &variance0);
	GetStats(rs.data(), rs.size(), &mean1, &variance1);
	//printf ("mean: %.3f -> %.3f, stddev: %.3f -> %.3f\n",  mean0, mean1, std::sqrt(variance0), std::sqrt(variance1));
	
	assert (rs.size() == validPoints.size());
	// filter reduces variance if not random image.
	assert (variance1 < variance0);

	// case 2. invalid(out-of-range) input
	invalidPoints[0] = {0, 0, 0};
	rs = offline::PointFilter(DP.data(), IR.data(), invalidPoints, patch_ht, patch_wd, 0);
	assert (rs.empty() == true);

	invalidPoints[0] = {32, 0, 0};

	return 0;
}

Point3Df_t RT_inverse(Point3Df_t p, float *RT)
{
	Point3Df_t oP;
	float64_t invRT[12];

	p.x -= RT[3];	
	p.y -= RT[7];	
	p.z -= RT[11];	
	
	invRT[0] = RT[0];
	invRT[1] = RT[4];
	invRT[2] = RT[8];

	invRT[4] = RT[1];
	invRT[5] = RT[5];
	invRT[6] = RT[9];

	invRT[8] = RT[2];
	invRT[9] = RT[6];
	invRT[10] = RT[10];

	oP.x = (invRT[0] * p.x) + (invRT[1] * p.y) + (invRT[2]  * p.z);
	oP.y = (invRT[4] * p.x) + (invRT[5] * p.y) + (invRT[6]  * p.z);
	oP.z = (invRT[8] * p.x) + (invRT[9] * p.y) + (invRT[10] * p.z);
	return oP;
}

Point3Df_t RT(Point3Df_t &p, float *RT)
{
	Point3Df_t oP;
	oP.x = (RT[0] * p.x) + (RT[1] * p.y) + (RT[2] * p.z)  + RT[3];
	oP.y = (RT[4] * p.x) + (RT[5] * p.y) + (RT[6] * p.z)  + RT[7];
	oP.z = (RT[8] * p.x) + (RT[9] * p.y) + (RT[10] * p.z) + RT[11];
	return oP;
}

int Example4_4_ExistsIn()
{
	// 3x4 RT = 3x3 rotation ++ 3x1 translation 
	float pfRT[12] = {
		0.998380, -0.023524,-0.051798, 1.151155,  
		-0.020392,-0.997978, 0.060195, -0.035638,  
		-0.053109,-0.059041,-0.996842, 1.218826};

	Point3Df_t w_0 = {1.1345, 0.1034, 0.7123};
	Point3Df_t c_0 = RT_inverse(w_0, pfRT);
	Point3Df_t w_1 = RT(c_0, pfRT);

	//printf("x:%.6f -> %.6f, y:%.6f -> %.6f, z:%.6f -> %.6f\n", w_0.x, w_1.x, w_0.y, w_1.y, w_0.z, w_1.z);
	//printf ("c.x: %.3f, c.y: %.3f, c.z: %.3f\n", c_0.x, c_0.y, c_0.z);

	// tolerable difference is up to THREED_LU_FLT_EPSION.
	assert (w_0 == w_1);

	bool exists = offline::ContainsPointCloud(w_0, pfRT);
	assert (true == exists);	

	return 0;
}

void GetFilteredPointCloudPatchHelper(std::vector<Point3Df_t> &out, std::string calibration_dir, std::string imageOA, std::string imageOR, int patch[4], FlipKind kFlip)
{
	bool bPrintWorldPoints = false;

	offline::InitializePreProcessing_core("non-exist", nullptr); // for forcing init
	ErrorType ret = offline::InitializePreProcessing_core((char*)calibration_dir.c_str(), nullptr);
	assert (SUCCESS == ret);
	offline::SetFlipMode(kFlip);

	std::vector<uint16_t> pusInDepth(640 * 480);
	std::vector<uint16_t> pusOutDepth(320 * 240);
	std::vector<uint16_t> pusInIR(640 * 480);
	std::vector<uint16_t> pusResizeIR(320 * 240);
	std::string outputImageDP = imageOR + "out." + std::to_string(kFlip) + ".raw";
	std::string outputImageIR = imageOA + "out." + std::to_string(kFlip) + ".raw";

	int nret = 0;

	nret = offline::LoadRaw(imageOR.c_str(), (char*)&pusInDepth[0], 640 * 480 * 2);
	assert(ret == 0);
	nret = offline::LoadRaw(imageOA.c_str(), (char*)&pusInIR[0], 640*480*2);
	assert(ret == 0);

	// input: VGA image frame

	nret = offline::Preprocessing_core_PL(&pusInDepth[0], &pusOutDepth[0], &pusInIR[0], &pusResizeIR[0]);
	assert(ret == SUCCESS);

	// output: QVGA image frame

	offline::SaveRaw(outputImageDP.c_str(), (char*)&pusOutDepth[0], 320*240*2);
	offline::SaveRaw(outputImageIR.c_str(), (char*)&pusResizeIR[0], 320*240*2);

	float pfRT[12] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 };
	int wd = 320;
	int ht = 240;
	int patch_y = patch[0];
	int patch_x = patch[1];
	int patchSize = patch[2];
	int iCameraIndex = 0;

	ret = offline::GetFilteredPointCloudPatch(&pusOutDepth[0], &pusResizeIR[0], &out, patch_y, patch_x, patchSize, patchSize, pfRT, wd, ht, 0, 2000, iCameraIndex);
	// verify return value
	assertInvalidResult(ret, out, patchSize * patchSize);

	if (bPrintWorldPoints)
	{
		for (auto p : out)
		{
			printf ("x:%f, y:%f, z:%f\n", p.x, p.y, p.z);
		}
	}

}





/*
 * END of APIs for Preprocessing on PL
 */


void Example5_LoadRaw()
{
	const int sz = 640 * 480 * 2;
	std::vector<uint16_t> expect(sz);

	for (int i = 0; i < 10000; i++)
	{
		assert (0 == LoadRaw("./TestFiles/C1/OR.raw", (char*)&expect[0], sz));
	}
}

void Example6_repeatExampleItself_for_sanitycheck()
{
	puts ("call Example4_GetFilteredPointCloudPatch() 1400 times");
	// just for checking leak or sanity check. meaningless
	for (int i = 0; i < 1400; i++)
	{
		Example4_GetFilteredPointCloudPatch();
	}
}

void Write2BinaryToText(const char *output, const char* buffer, int len)
{
	FILE *f = fopen(output, "w");
	uint16_t *p = (uint16_t*)buffer;
	if (f)
	{
		for (int i = 0; i < len/2; i++)
		{
			fprintf(f, "%04x\n", p[i]);
		}
		fclose(f);
	}
	else
	{
		printf ("fail to open %s\n", output);
	}
}

void Write4BinaryToText(const char *output, const char* buffer, int len)
{
	FILE *f = fopen(output, "w");
	uint32_t *p = (uint32_t*)buffer;
	if (f)
	{
		for (int i = 0; i < len/4; i++)
		{
			fprintf(f, "%08x\n", p[i]);
		}
		fclose(f);
	}
	else
	{
		printf ("fail to open %s\n", output);
	}

}

void Example7_Preprocessing_core_PL_goldenset_test()
{
	assert(SUCCESS == offline::InitializePreProcessing_core("./params/C1_goldenset/", nullptr));
	const int sz_input = 640 * 480;
	const int sz_output = 320 * 240;
	const int sz_pixel = sizeof(uint16_t);
	const int sz_input_bytes = sz_input * sz_pixel;
	const int sz_output_bytes = sz_output * sz_pixel;

	std::vector<uint16_t> pusInDepth(sz_input);
	std::vector<uint16_t> pusOutDepth(sz_output);
	std::vector<uint16_t> pusInIR(sz_input);
	std::vector<uint16_t> pusResizeIR(sz_output);

	// Dump PL register for setting calibration parameters
	// 	PL_BUFFER: params->PL_offset ++ params->is_available == 1980 (1260 + 720) bytes
	//	PL_COEF: params->coef_curve ++ params->coef_slope == 4 + 4 bytes
	char buffer[1980];
	PreprocessorParams *params = offline::GetCameraParam(0);

	int32_t coef_curve = params->coef_curve;
	int32_t coef_slope = params->coef_slope;

	memcpy (buffer, params->PL_offset, sizeof(params->PL_offset));
	assert (1260 == sizeof(params->PL_offset));

	memcpy (buffer + sizeof(params->PL_offset), params->PL_available, sizeof(params->PL_available));
	assert (720 == sizeof(params->PL_available));

	Write4BinaryToText("params/C1_goldenset/PL_OFFSET_AVAILABLE.txt", buffer, 1980);

	memcpy (buffer, (char*)&coef_curve, sizeof(int32_t));
	memcpy (buffer + sizeof(int32_t), (char*)&coef_slope, sizeof(int32_t));

	Write4BinaryToText("params/C1_goldenset/PL_CURVE_SLOPE.txt", buffer, 8);

	assert (0 == offline::LoadRaw("./params/C1_goldenset/LG_OR_00407.raw", (char*)&pusInDepth[0], sz_input_bytes));
	assert (0 == offline::LoadRaw("./params/C1_goldenset/LG_OA_00407.raw", (char*)&pusInIR[0], sz_input_bytes));

	Write2BinaryToText("./params/C1_goldenset/OR.txt", (char*)&pusInDepth[0], sz_input_bytes);
	Write2BinaryToText("./params/C1_goldenset/OA.txt", (char*)&pusInIR[0], sz_input_bytes);

	// input: VGA image frame
	assert(SUCCESS == offline::Preprocessing_core_PL(&pusInDepth[0], &pusOutDepth[0], &pusInIR[0], &pusResizeIR[0]));
	// result: QVGA image frame

	uint32_t actual_crc_3d = getCRC32((void*)&pusOutDepth[0], sz_output_bytes);
	uint32_t actual_crc_2d = getCRC32((void*)&pusResizeIR[0], sz_output_bytes);
	uint32_t expect_crc_3d = 0x48c7f14c;
	uint32_t expect_crc_2d = 0x853b60ff;

	offline::SaveRaw("./params/C1_goldenset/actual_OR.raw", (char*)&pusOutDepth[0], sz_output_bytes);
	offline::SaveRaw("./params/C1_goldenset/actual_OA.raw", (char*)&pusResizeIR[0], sz_output_bytes);

	assert (expect_crc_3d == actual_crc_3d);
	assert (expect_crc_2d == actual_crc_2d);

	// dump PL register setting and output as plain text (2 bytes read)
	Write2BinaryToText("./params/C1_goldenset/actual_OR.txt", (char*)&pusOutDepth[0], sz_output_bytes);
	Write2BinaryToText("./params/C1_goldenset/actual_OA.txt", (char*)&pusResizeIR[0], sz_output_bytes);
}

void Example8_GetPixelXYPoint()
{
	int wd = 640;
	int ht = 480;
	int wd_out = 320;
	int ht_out = 240;
	bool isQVGA = true;


	std::vector<uint16_t> pusInDepth(wd * ht);
	std::vector<uint16_t> pusOutDepth(wd_out * ht_out);
	std::vector<uint16_t> pusInIR(wd * ht);
	std::vector<uint16_t> pusOutIR(wd_out * ht_out);
	std::string dir = "TestFiles/pointfilter/";

	setup(pusInDepth, pusInIR,
		(char*)dir.c_str(), (char*)(dir + "DP.in.raw").c_str(), (char*)(dir + "IR.in.raw").c_str());

	int ret = Preprocessing_core_PL(&pusInDepth[0], &pusOutDepth[0], &pusInIR[0], &pusOutIR[0]);
	assert (SUCCESS == ret);
	offline::SaveRaw((dir + "DP.out.raw").c_str(), (char*)pusOutDepth.data(), wd_out * ht_out * 2);

	std::vector<Point3Du_t> arImagePoint;	// in
	std::vector<Point3Df_t> arWorldPoint;	// out

	float pfRT[12] = {
		 0.998380,-0.023524,-0.051798,  1.151155,  
		-0.020392,-0.997978, 0.060195, -0.035638,  
		-0.053109,-0.059041,-0.996842,  1.218826};
		 
	uint16_t u = 111;
	uint16_t v = 50;
	uint16_t r = pusOutDepth[v * wd_out + u];
	int iCameraIndex = 0;

	arImagePoint.push_back({u, v, r});

	ret = offline::GetPointCloudArray_3d(&arImagePoint, &arWorldPoint, pfRT, wd_out, ht_out, 0, 2000, iCameraIndex);

	assert(SUCCESS == ret);

	float32_t x = arWorldPoint[0].x;
	float32_t y = arWorldPoint[0].y;
	float32_t z = arWorldPoint[0].z;
	float32_t u2;
	float32_t v2;

	// output u2, v2 is based on VGA image
	bool r2 = offline::GetPixelXY(x, y, z, u2, v2, pfRT, 0);
	if (isQVGA)
	{
		u2 /= 2;
		v2 /= 2;
	}
	printf ("GetPointCloudArray_3d: u:%d, v:%d, r: %d --> x:%f, y:%f, z:%f\n", u, v, r, x, y, z);
	printf ("GetPixelXY: x:%f, y:%f, z:%f --> u:%f, v:%f\n", x, y, z, u2, v2);

	// simple check. difference should be smaller than 1 pixel
	assert (fabs(u2 - u) < 1.f);
	assert (fabs(v2 - v) < 1.f);
}

void Example9_ExportSensorPointAsPLY_Nilesh()
{
	int wd = 640;
	int ht = 480;
	int ret;

	std::vector<uint16_t> pusInDepth(wd * ht);
	std::vector<uint16_t> pusOutDepth(wd * ht);
	std::vector<uint16_t> pusInIR(wd * ht);
	std::vector<uint16_t> pusOutIR(wd * ht);

	std::string dir("./TestFiles/HADASOMS-844/");
	std::string outfile = dir + "HADASOMS-844.ply";
	std::string DP = dir + "D.raw";
	std::string IR = dir + "A.raw";
	setup(pusInDepth, pusInIR,
				dir.c_str(), DP.c_str(), IR.c_str());

	std::vector<Point3Du_t> arImage;
	std::vector<Point3Df_t> arWorld;
	std::vector<Point3D_t> arPoint;
	arPoint.clear();

	// 1. preprocessing
	ret = offline::Preprocessing_core_PL(&pusInDepth[0], &pusOutDepth[0], &pusInIR[0], &pusOutIR[0]);
	assert(SUCCESS == ret);

	// 2. 3D Look-up
	float pfRT[12] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 };
	offline::GetFilteredPointCloudPatch(pusOutDepth.data(), pusOutIR.data(), &arWorld, 0, 0, 240, 320, pfRT, 320, 240, 0, 2000, 0);

	// 3. Export points as PLY format
	for (auto p: arWorld)
	{
		Point3D_t point;
		point.x = p.x;
		point.y = p.y;
		point.z = p.z;
		offline::ColorDepthPixel_3d(point.z, 2.0f, point.R, point.G, point.B);
		arPoint.push_back(point);
	}
	offline::ExportSensorPointsAsPLY(&arPoint, (char*)outfile.c_str());
}


void Example9_ExportSensorPointAsPLY()
{
	int wd = 640;
	int ht = 480;
	ErrorType ret;

	std::vector<uint16_t> pusInDepth(wd * ht);
	std::vector<uint16_t> pusOutDepth(wd * ht);
	std::vector<uint16_t> pusInIR(wd * ht);

	setup(pusInDepth, pusInIR,
				"./params/C1/", "./TestFiles/C1/OR.raw", "./TestFiles/C1/OA.raw");

	std::vector<Point3Du_t> arImage;
	std::vector<Point3Df_t> arWorld;
	std::vector<Point3D_t> arPoint;
	arPoint.clear();

	// 1. preprocessing
	ret = Preprocessing_core_PS(&pusInDepth[0], &pusOutDepth[0], &pusInIR[0]);
	assert(SUCCESS == ret);

	for (uint16_t y = 0; y < 480; y++)
	{
		for (uint16_t x = 0; x < 640; x++)
		{
			uint16_t r = pusOutDepth[y * 640 + x];
			arImage.push_back({x, y, r});
		}
	}

	// 2. 3D Look-up
	float pfRT[12] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 };
	ret = offline::GetPointCloudArray_3d(&arImage, &arWorld, pfRT, 640, 480, 0, 2000, 0);
	assert(SUCCESS == ret);

	// 3. Export points as PLY format
	Point3D_t point;
	for (int nv = 0; nv < ht; nv++)
	{
		for (int nu = 0; nu < wd; nu++)
		{
			int index = nv * wd + nu;
			if (arWorld[index].z != 0)
			{
				point.x = arWorld[index].x;
				point.y = arWorld[index].y;
				point.z = arWorld[index].z;
				offline::ColorDepthPixel_3d(point.z, 2.0f, point.R, point.G, point.B);
				arPoint.push_back(point);
			}
		}
	}
	offline::ExportSensorPointsAsPLY(&arPoint, "./TestFiles/C1/Ex9_LG_PC.ply");
}

void Example10_Preprocessing_core_PS_elapsed_time()
{
	int wd = 640;
	int ht = 480;
	ErrorType ret;

	std::vector<uint16_t> pusInDepth(wd * ht);
	std::vector<uint16_t> pusOutDepth(wd * ht);
	std::vector<uint16_t> pusInIR(wd * ht);
	std::vector<long long> times;

	setup(pusInDepth, pusInIR,
		"./params/C1/", "./TestFiles/C1/OR.raw", "./TestFiles/C1/OA.raw");

	for (int i = 0; i < 32; i++)
	{
		std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

		ret = Preprocessing_core_PS(&pusInDepth[0], &pusOutDepth[0], &pusInIR[0]);
		assert(SUCCESS == ret);

		std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
		std::chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		times.push_back(elapsed.count());
	}

	long long minimum = 1E9;
	long long maximum = 0;
	float average = 0;
	long long sum = 0;

	for (auto &elapsed : times)
	{
		minimum = std::min(minimum, elapsed);
		maximum = std::max(maximum, elapsed);
		sum += elapsed;
	}
	average = (float)sum / times.size();

	printf("[PP-on-PS] avg: %f ms, max: %d ms, min: %d ms\n", average, maximum, minimum);
	(void)pusOutDepth[640*240 + 320];
}

void Example11_Preprocessing_core_PL_elapsed_time()
{
	int wd = 640;
	int ht = 480;
	int ret;

	std::vector<uint16_t> pusInDepth(wd * ht);
	std::vector<uint16_t> pusOutDepth(wd * ht / 2);
	std::vector<uint16_t> pusInIR(wd * ht);
	std::vector<uint16_t> pusOutIR(wd * ht / 2);
	std::vector<long long> times;

	setup(pusInDepth, pusInIR,
		"./TestFiles/C1-R9.0.0.8/",
		"./TestFiles/C1-R9.0.0.8/5_2D.in.raw",
		"./TestFiles/C1-R9.0.0.8/5_3D.in.raw");

	for (int i = 0; i < 32; i++)
	{
		std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

		ret = Preprocessing_core_PL(&pusInDepth[0], &pusOutDepth[0], &pusInIR[0], &pusOutIR[0]);
		assert(SUCCESS == ret);

		std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
		std::chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		times.push_back(elapsed.count());
	}

	long long minimum = 1E9;
	long long maximum = 0;
	float average = 0;
	long long sum = 0;

	for (auto &elapsed : times)
	{
		minimum = std::min(minimum, elapsed);
		maximum = std::max(maximum, elapsed);
		sum += elapsed;
	}
	average = (float)sum / times.size();

	printf("[PP-on-PL] avg: %f ms, max: %d ms, min: %d ms\n", average, maximum, minimum);
	(void)pusOutDepth[320 * 120 + 160];
}

int LoadImage(std::string file, void *buffer, int nSize)
{
	int ret = 0;
	if (file.rfind("raw") != std::string::npos)
	{
		ret = offline::LoadRaw(file.c_str(), (char*)buffer, nSize);
		return ret < 0;
	}
	else if (file.rfind("png") != std::string::npos)
	{
		offline::LoadPNG(file.c_str(), (char*)buffer, nSize);
		return 0;
	}
	return -1;
}


void testPreprocessing_core_PL(char *test_dir, enum APVersion version, FlipKind kFlip, int nIgnoreFirstFrame, uint32_t nTolerancePixelDiff, uint32_t nToleranceDiffCount)
{
	auto getDiffPixels = [&] (uint16_t *expect, uint16_t *actual, int32_t nPixels, int32_t tolerancePixelDiff) {
		uint32_t count = 0;
		for (int i = 0; i < nPixels; i++)
		{
			count += (abs(expect[i] - actual[i]) > tolerancePixelDiff);
		}
		return count;
	};
	// if cannot find 'substr', 'replace' is appended
	auto stringReplace = [&](const std::string &a, const char* substr, const char* replace) {
		size_t pos = a.find(substr);
		if (pos != std::string::npos)
		{
			std::string front = a.substr(0, pos);
			std::string tail = a.substr(pos + strlen(substr));
			return front + replace + tail;
		}
		return a + "." + replace;
	};

	int wd = 640;
	int ht = 480;
	int vga = wd * ht;
	int qvga = wd/2 * ht/2;
	int bytes_vga = vga * 2;
	int bytes_qvga = qvga * 2;
	int nExactMatchFrames = 0;
	int nAllFrames = 0;

	float avgDifferentPixels2D = 0.f;
	float avgDifferentPixels3D = 0.f;

	bool saveAlways = true;

	std::vector<uint16_t> pusInDepth(wd * ht);
	std::vector<uint16_t> pusOutDepth(wd/2 * ht/2);
	std::vector<uint16_t> pusOutDepthExpect(wd/2 * ht/2);
	std::vector<uint16_t> pusInIR(wd * ht);
	std::vector<uint16_t> pusOutIR(wd/2 * ht/2);
	std::vector<uint16_t> pusOutIRExpect(wd/2 * ht/2);

	std::vector<std::string> inputs2D;
	std::vector<std::string> inputs3D;
	std::vector<std::string> results2D;
	std::vector<std::string> results3D;

	int ret = offline::InitializePreProcessing_core(test_dir, version);
	assert (SUCCESS == ret);

	if (kFlip != FLIP_NORMAL)
	{
		printf ("Set Flip Mode %d\n", kFlip);
		offline::SetFlipMode(kFlip);
	}

	// prepare input, results files
	ret = LoadTestFiles(test_dir, inputs2D, inputs3D, results2D, results3D);

	assert (SUCCESS == ret);

	for (int i = 0; i < inputs2D.size(); i++)
	{
		std::string input2D = (std::string(test_dir) + inputs2D[i]);
		std::string input3D = (std::string(test_dir) + inputs3D[i]);

		ret =  LoadImage(input3D, (char*)&pusInDepth[0], bytes_vga);
		assert(ret == 0);
		ret = LoadImage(input2D, (char*)&pusInIR[0], bytes_vga);
		assert(ret == 0);

		int ret = offline::Preprocessing_core_PL(&pusInDepth[0], &pusOutDepth[0], &pusInIR[0], &pusOutIR[0]);
		assert (SUCCESS == ret);

		// if expect result is available, compare the result
		if (i < results2D.size())
		{
			if (nIgnoreFirstFrame > 0)
			{
				--nIgnoreFirstFrame;
				continue;
			}
			++nAllFrames;
			std::string expect2D = (std::string(test_dir) + results2D[i]);
			std::string expect3D = (std::string(test_dir) + results3D[i]);
			LoadImage(expect2D, (char*)&pusOutIRExpect[0], bytes_qvga);
			LoadImage(expect3D, (char*)&pusOutDepthExpect[0], bytes_qvga);

			int nDiffPixels2D = getDiffPixels(&pusOutIRExpect[0], &pusOutIR[0], qvga, REGRESSION_TEST_TOLERANCE_PIXEL_WISE_DIFF);
			int nDiffPixels3D = getDiffPixels(&pusOutDepthExpect[0], &pusOutDepth[0], qvga, REGRESSION_TEST_TOLERANCE_PIXEL_WISE_DIFF);

			avgDifferentPixels2D += nDiffPixels2D;
			avgDifferentPixels3D += nDiffPixels3D;

			bool exact2D = checkArray(&pusOutIRExpect[0], &pusOutIR[0], qvga);
			bool exact3D = checkArray(&pusOutDepthExpect[0], &pusOutDepth[0], qvga);

			//printf ("[%d] Diff.Pixels {2D: %d, 3D: %d} - %s\n", nAllFrames, nDiffPixels2D, nDiffPixels3D, expect3D.c_str());

			if (exact2D && exact3D) ++nExactMatchFrames;


			if (saveAlways || !exact2D)
			{
				std::string out = stringReplace(expect2D, "expect", (!exact2D) ? "actual-fail" : "actual");
				offline::SaveRaw(out.c_str(), (char*)&pusOutIR[0], bytes_qvga);
			}
			if (saveAlways || !exact3D)
			{
				std::string out = stringReplace(expect3D, "expect", (!exact3D) ? "actual-fail" : "actual");
				offline::SaveRaw(out.c_str(), (char*)&pusOutDepth[0], bytes_qvga);
			}

			assert (nDiffPixels2D <= nToleranceDiffCount);
			assert (nDiffPixels3D <= nToleranceDiffCount);
		}
	}

	if (results2D.size() <= 0) return;

	float exactMatchRatio = ((float)(nExactMatchFrames*100)/nAllFrames);
	printf ("[PASS] AVG. DIFFERENT PIXELS: {2D: %.1f, 3D: %.1f}, diff. count tolerance: %d, pixel wise diff. tolerance: %d\n",
		avgDifferentPixels2D/nAllFrames, avgDifferentPixels3D/nAllFrames, nToleranceDiffCount, nTolerancePixelDiff);

	printf ("    # of matching frames in total: %d/%d, exact matching ratio: %.2f %\n",
		nExactMatchFrames, nAllFrames, exactMatchRatio);
}

void Example12_Preprocessing_core_PL_RegressionTest()
{
	puts ("\n===== Regression Test for R9.0.0.6 =====");
	testPreprocessing_core_PL("./TestFiles/C1-R9.0.0.6/", APVersion::R9_0_0_6);

	puts ("\n===== Regression Test for R9.0.0.8 =====");
	testPreprocessing_core_PL("./TestFiles/C1-R9.0.0.8/", APVersion::R9_0_0_8);

	puts ("\n===== Regression Test for R9.0.1.0 =====");
	testPreprocessing_core_PL("./TestFiles/C1-R9.0.1.0/", APVersion::R9_0_1_0);

	puts ("\n===== Regression Test for R9.1.1.0 =====");
	testPreprocessing_core_PL("./TestFiles/C1-R9.1.1.0/", APVersion::LATEST);

	puts ("\n===== Regression Test for R10.0.1.0 =====");
	testPreprocessing_core_PL("./TestFiles/C1-R10.0.1.0/", APVersion::LATEST);

	puts ("\n===== Regression Test for R10.0.1.0 (H/W SSR: 64) =====");
	testPreprocessing_core_PL("./TestFiles/D-R10.0.1.0/", APVersion::LATEST);

	puts ("\n===== Regression Test for R10.2.1.0 =====");
	testPreprocessing_core_PL("./TestFiles/D-R10.2.1.0/", APVersion::LATEST);

	puts ("\n===== Regression Test for R10.4.0.3 =====");
	testPreprocessing_core_PL("./TestFiles/D-R10.4.0.3/", APVersion::LATEST);

	puts ("\n===== Regression Test for R10.4.0.3 (FLIP1: UP_DOWN) =====");
	testPreprocessing_core_PL("./TestFiles/D-R10.4.0.3_FLIP1/", APVersion::LATEST, FLIP_VERTICAL);

	puts ("\n===== Regression Test for R10.4.0.3 (FLIP2: RIGHT_LEFT) =====");
	testPreprocessing_core_PL("./TestFiles/D-R10.4.0.3_FLIP2/", APVersion::LATEST, FLIP_HORIZONTAL);

	puts ("\n===== Regression Test for R10.4.0.3 (FLIP3: BOTH_DIRECTION) =====");
	testPreprocessing_core_PL("./TestFiles/D-R10.4.0.3_FLIP3/", APVersion::LATEST, FLIP_BOTH);

	puts ("\n===== Regression Test for R10.4.2.0 =====");
	testPreprocessing_core_PL("./TestFiles/D-R10.4.2.0/", APVersion::LATEST);

	puts ("\n===== Regression Test for R10.4.3.1 =====");
	testPreprocessing_core_PL("./TestFiles/D-R10.4.3.1/", APVersion::LATEST);

	puts ("\n===== Regression Test for R10.4.3.5 =====");
	testPreprocessing_core_PL("./TestFiles/D-R10.4.3.5/", APVersion::LATEST);

	puts ("\n===== Regression Test for R11.3.4.1 =====");
	testPreprocessing_core_PL("./TestFiles/D-R11.3.4.1/", APVersion::LATEST);
	puts ("\n===== Regression Test for D-R11.4.3.1 =====");
	testPreprocessing_core_PL("./TestFiles/D-R11.4.3.1/", APVersion::LATEST);
	// Similarity Test check whether the difference is in the sample's deviation.
	uint32_t nToleranceDiffCount = 320 * 240;
	uint32_t nTolerancePixelDiff = 200;
	printf ("\n===== Similarity Test for R9.0.0.8 between C1 and D (pixel-wise diff. tolerance: %d) =====\n", nTolerancePixelDiff);
	testPreprocessing_core_PL("./TestFiles/SampleDifferenceTest_R-9.0.0.8-C1_VS_D/", APVersion::R9_0_0_8, FLIP_NORMAL, 2, nTolerancePixelDiff, nToleranceDiffCount);
}

bool checkArray(uint16_t *expect, uint16_t *actual, int sz)
{
	for (int i = 0; i < sz; i++)
	{
		if (expect[i] != actual[i])
		{
			return false;
		}
	}
	return true;
}

void assertArray(uint16_t *expect, uint16_t *actual, int sz)
{
	for (int i = 0; i < sz; i++)
	{
		if (expect[i] == actual[i])
		{
		}
		assert (expect[i] == actual[i]);
	}
}

// load image frame and initialize preprocessor
void setup(std::vector<uint16_t> &inDepth, std::vector<uint16_t> &inIR, const char *paramDir, const char *path_3D, const char *path_2D, enum APVersion version)
{
	int wd = 640;
	int ht = 480;

 	assert (0 == offline::LoadRaw(path_3D, (char*)&inDepth[0], wd * ht * 2));
	assert (0 == offline::LoadRaw(path_2D, (char*)&inIR[0], wd * ht * 2));

	ErrorType ret = offline::InitializePreProcessing_core((char*)paramDir, version);
	assert (SUCCESS == ret);
}


// input file pattern: [0-9]\+_2D.in.raw, [0-9]\+_3D.in.raw
// output file pattern: [0-9]\+_2D.expect.raw, [0-9]\+_3D.expect.raw
// @result: 0 for success, -1 otherwise
int LoadTestFiles(const char* test_dir, std::vector<std::string> &inputs2D, std::vector<std::string> &inputs3D, std::vector<std::string> &results2D, std::vector<std::string> &results3D)
{
	auto comparePrefixNumber = [&](const std::string &a, const std::string &b) {
		auto prefixNumber = [&](const std::string &a) {
			const char *p = a.c_str();
			std::string num("0");
			for (; p != NULL && isdigit(*p); ++p)
			{
				num.push_back(*p);
			}
			return atoi(num.c_str());
		};

		int a_num = prefixNumber(a);
		int b_num = prefixNumber(b);
		return a_num < b_num;
	};
#ifndef _WIN32
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (test_dir)) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL) {
			std::string name(ent->d_name);
			if (name.find("2D.in.raw") != std::string::npos || name.find("2D.in.png") != std::string::npos)
			{
				inputs2D.push_back(name);
			}
			else if (name.find("3D.in.raw") != std::string::npos || name.find("3D.in.png") != std::string::npos)
			{
				inputs3D.push_back(name);
			}
			else if (name.find("2D.expect.raw") != std::string::npos || name.find("2D.expect.png") != std::string::npos)
			{
				results2D.push_back(name);
			}
			else if (name.find("3D.expect.raw") != std::string::npos || name.find("3D.expect.png") != std::string::npos)
			{
				results3D.push_back(name);
			}
		}


		std::sort(inputs2D.begin(), inputs2D.end(), comparePrefixNumber);
		std::sort(inputs3D.begin(), inputs3D.end(), comparePrefixNumber);
		std::sort(results2D.begin(), results2D.end(), comparePrefixNumber);
		std::sort(results3D.begin(), results3D.end(), comparePrefixNumber);

		closedir (dir);
	} else {
		/* could not open directory */
		perror ("");
		return -1;
	}
#else
	typedef std::wstring str;
	typedef wchar_t str_t;
	std::vector<str> res_files;
	std::vector<str> cur_files;
	
	auto c2w = [](const char* in)->str {
		std::string t(in);
		return str(t.begin(), t.end());
	};

	auto ls = [&](str path)->std::vector<str> {
		std::vector<str> ret;
		WIN32_FIND_DATA fdFile;
		HANDLE hFind = NULL;

		str fpath = path + L"*.*";

		if ((hFind = FindFirstFile(fpath.c_str(), &fdFile)) == INVALID_HANDLE_VALUE)
		{
			printf("Path not found: [%s]\n", path.c_str());
		}
		do
		{
			if (strcmp((char*)fdFile.cFileName, ".") != 0
				&& strcmp((char*)fdFile.cFileName, "..") != 0)
			{
				str rpath = str(fdFile.cFileName);
				ret.push_back(rpath);

				//Is the entity a File or Folder?
				//if (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
			}
		} while (FindNextFile(hFind, &fdFile)); //Find the next file.
		FindClose(hFind); //Always, Always, clean things up!
		return ret;
	};

	cur_files = ls(c2w(test_dir));
	for (auto &x : cur_files)
	{
		std::string name(x.begin(), x.end());
		if (name.find("2D.in.raw") != std::string::npos || name.find("2D.in.png") != std::string::npos)
		{
			inputs2D.push_back(name);
		}
		else if (name.find("3D.in.raw") != std::string::npos || name.find("3D.in.png") != std::string::npos)
		{
			inputs3D.push_back(name);
		}
		else if (name.find("2D.expect.raw") != std::string::npos || name.find("2D.expect.png") != std::string::npos)
		{
			results2D.push_back(name);
		}
		else if (name.find("3D.expect.raw") != std::string::npos || name.find("3D.expect.png") != std::string::npos)
		{
			results3D.push_back(name);
		}
	}
	std::sort(inputs2D.begin(), inputs2D.end(), comparePrefixNumber);
	std::sort(inputs3D.begin(), inputs3D.end(), comparePrefixNumber);
	std::sort(results2D.begin(), results2D.end(), comparePrefixNumber);
	std::sort(results3D.begin(), results3D.end(), comparePrefixNumber);
#endif

	// expects the same number of 2D, 3D input
	// expects the same number of 2D, 3D output
	if (inputs2D.size() != inputs3D.size())
	{
		printf ("Mismatch input files. (2D: %d files, 3D: %d files)\n", inputs2D.size(), inputs3D.size());
		return -1;
	}
	if (results2D.size() != results3D.size())
	{
		printf ("Mismatch expected files. (2D: %d files, 3D: %d files)\n", results2D.size(), results3D.size());
		return -1;
	}
	return 0;
}

void Example13_GetInvalidMask()
{
	ErrorType ret = offline::InitializePreProcessing_core("./TestFiles/C1-R9.0.0.6/");
	assert (ret == SUCCESS);

	std::vector<uint16_t> invalidMask = offline::GetInvalidMask(0);
	assert (invalidMask.size() == 640 * 480);

	int step = 8;
	bool show = false;

	for (int y = 0; y < 480 / step; y++)
	{
		for (int x = 0; x < 640 / step; x++)
		{
			int y_idx = y * step;
			int x_idx = x * step;
			// invalid pixels are set to 1. valid pixels are 0
			bool isInavlid = (invalidMask[(y_idx * 640) + x_idx] == 1);
			if (show) printf ("%s", isInavlid ? "X" : ".");
		}
		if (show) puts ("");
	}
}

void Example14_GetRTMatrix()
{
	float32_t fRT[12];
	bool ret = offline::GetRTMatrix("no-such-file", fRT);
	assert (ret == false);

	ret = offline::GetRTMatrix("./TestFiles/omscal_exrinsic_106012875.bin", fRT);
	assert (ret = true);

	printf ("RT[0~11] : %f,%f,%f,%f,  %f,%f,%f,%f,  %f,%f,%f,%f\n",
		fRT[0], fRT[1], fRT[2], fRT[3],
		fRT[4], fRT[5], fRT[6], fRT[7],
		fRT[8], fRT[9], fRT[10], fRT[11]);
}

void Example15_GetPointCloudPatch_MinModel()
{
	std::string paramDir("./TestFiles/MIN-R2.1/");
	bool bPrintWorldPoints = true;

	ErrorType ret = offline::InitializePreProcessing_core((char*)paramDir.c_str(), 2);
	assert (SUCCESS == ret);

	std::vector<uint16_t> pusInDepth(640 * 480);
	std::vector<uint16_t> pusOutDepth(640 * 480);
	std::vector<uint16_t> pusInIR(640 * 480);
	std::vector<uint16_t> pusResizeIR(640 * 480);

	assert (0 == offline::LoadRaw((paramDir + "OR.raw").c_str(), (char*)&pusInDepth[0], 640*480*2));
	assert (0 == offline::LoadRaw((paramDir + "OA.raw").c_str(), (char*)&pusInIR[0], 640*480*2));

	// input: VGA image frame

	assert(SUCCESS == offline::Preprocessing_core_PL(&pusInDepth[0], &pusOutDepth[0], &pusInIR[0], &pusResizeIR[0], eCameraPosition::FrontLeft));
	assert(SUCCESS == offline::Preprocessing_core_PL(&pusInDepth[0], &pusOutDepth[0], &pusInIR[0], &pusResizeIR[0], eCameraPosition::FrontRight));

	// output: QVGA image frame

	offline::SaveRaw("./TestFiles/C1/Ex4_OR_result.raw", (char*)&pusOutDepth[0], 320*240*2);
	offline::SaveRaw("./TestFiles/C1/Ex4_OA_result.raw", (char*)&pusResizeIR[0], 320*240*2);

	std::vector<Point3Df_t> arWorldPoint;
	std::vector<Point3Df_t> arWorldPoint2;

	float pfRT[12] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 };
	int wd = 320;
	int ht = 240;
	int patch_y = ht / 2;
	int patch_x = wd / 2;
	int patchSize = 12;
	int iCameraIndex = 0;

	ret = offline::GetFilteredPointCloudPatch(&pusOutDepth[0], &pusResizeIR[0], &arWorldPoint, patch_y, patch_x, patchSize, patchSize, pfRT, eCameraPosition::FrontLeft);

	assertInvalidResult(ret, arWorldPoint, patchSize * patchSize);
	assert(patchSize * patchSize == arWorldPoint.size());

	if (bPrintWorldPoints)
	{
		for (auto p : arWorldPoint)
		{
			printf ("x:%f, y:%f, z:%f\n", p.x, p.y, p.z);
		}
	}

	ret = offline::GetFilteredPointCloudPatch(&pusOutDepth[0], &pusResizeIR[0], &arWorldPoint2, patch_y, patch_x, patchSize, patchSize, pfRT, eCameraPosition::FrontRight);

	assertInvalidResult(ret, arWorldPoint, patchSize * patchSize);
	assert(patchSize * patchSize == arWorldPoint2.size());

	if (bPrintWorldPoints)
	{
		for (auto p : arWorldPoint2)
		{
			printf ("x:%f, y:%f, z:%f\n", p.x, p.y, p.z);
		}
	}
}

void Example16_GetHalfResize_core_MinModel()
{
	int wd = 640;
	int ht = 480;
	std::vector<uint16_t> pusInDepth(wd * ht);
	std::vector<uint16_t> pusInIR(wd * ht);
	std::vector<uint16_t> pusOutDepth(wd/2 * ht/2);	// QVGA
	std::vector<uint16_t> pusOutIR(wd/2 * ht/2);	// QVGA

 	assert (0 == offline::LoadRaw("./TestFiles/MIN-R2.1/OR.raw", (char*)&pusInDepth[0], wd * ht * 2));
 	assert (0 == offline::LoadRaw("./TestFiles/MIN-R2.1/OA.raw", (char*)&pusInIR[0], wd * ht * 2));
	offline::GetHalfResize_core(&pusInDepth[0], &pusOutDepth[0], &pusInIR[0], &pusOutIR[0]);
	assert (0 == offline::SaveRaw("./TestFiles/MIN-R2.1/OR.out.raw", (char*)&pusOutDepth[0], wd/2 * ht/2 * 2));
	assert (0 == offline::SaveRaw("./TestFiles/MIN-R2.1/OA.out.raw", (char*)&pusOutIR[0], wd/2 * ht/2 * 2));
}


void Example17_Preprocessing_core_PL_MinModel()
{
	std::vector<uint16_t> pusInDepth_R(N_VGA_PIXELS);
	std::vector<uint16_t> pusInDepth_L(N_VGA_PIXELS);
	std::vector<uint16_t> pusInIR_R(N_VGA_PIXELS);
	std::vector<uint16_t> pusInIR_L(N_VGA_PIXELS);

	std::vector<uint16_t> pusOutDepth_R(N_QVGA_PIXELS);
	std::vector<uint16_t> pusOutDepth_L(N_QVGA_PIXELS);
	std::vector<uint16_t> pusOutIR_R(N_QVGA_PIXELS);
	std::vector<uint16_t> pusOutIR_L(N_QVGA_PIXELS);

	std::string testDir("./TestFiles/MIN-R2.1/");
	int ret;

	ErrorType r = offline::InitializePreProcessing_core((char*)testDir.c_str(), 2);
	assert (SUCCESS == r);

	assert (0 == offline::LoadRaw((testDir + "0_0_3D.raw").c_str(), (char*)&pusInDepth_R[0], N_VGA_BYTES));
	assert (0 == offline::LoadRaw((testDir + "0_1_3D.raw").c_str(), (char*)&pusInDepth_L[0], N_VGA_BYTES));
	assert (0 == offline::LoadRaw((testDir + "0_0_2D.raw").c_str(), (char*)&pusInIR_R[0], N_VGA_BYTES));
	assert (0 == offline::LoadRaw((testDir + "0_1_2D.raw").c_str(), (char*)&pusInIR_L[0], N_VGA_BYTES));


	ret = offline::Preprocessing_core_PL(&pusInDepth_R[0], &pusOutDepth_R[0], &pusInIR_R[0], &pusOutIR_R[0], eCameraPosition::FrontRight);
	assert (SUCCESS == ret);

	ret = offline::Preprocessing_core_PL(&pusInDepth_L[0], &pusOutDepth_L[0], &pusInIR_L[0], &pusOutIR_L[0], eCameraPosition::FrontLeft);
	assert (SUCCESS == ret);

	assert (0 == offline::SaveRaw((testDir + "0_0_3D.out.raw").c_str(), (char*)&pusOutDepth_R[0], N_QVGA_BYTES));
	assert (0 == offline::SaveRaw((testDir + "0_1_3D.out.raw").c_str(), (char*)&pusOutDepth_L[0], N_QVGA_BYTES));
	assert (0 == offline::SaveRaw((testDir + "0_0_2D.out.raw").c_str(), (char*)&pusOutIR_R[0], N_QVGA_BYTES));
	assert (0 == offline::SaveRaw((testDir + "0_1_2D.out.raw").c_str(), (char*)&pusOutIR_L[0], N_QVGA_BYTES));

	bool pass_2d = checkArray(pusOutIR_R.data(), pusOutIR_L.data(), N_QVGA_PIXELS);
	assert (true == pass_2d);

	bool pass_3d = checkArray(pusOutDepth_R.data(), pusOutDepth_L.data(), N_QVGA_PIXELS);
	assert (true == pass_3d);
}

void Example18_OnlineCalibration_TestOperation()
{
	int32_t nRet;

	nRet = offline::TestOnlineCalibration("D:\\LoggingData\\2point_cal.dat", 167, 8, 0);
	//"D:/Record/OnlineCalibration_TESTCASE/20180329_#2/graragecar/1.dat"
	//"D:/Record/177_for_online_calibration.dat"
	//"D:/Record/OnlineCalibration_TESTCASE/20180329_#2/normal with number2/2_normal.dat"
}

void Example19_OnlineCalibration_Validation()
{
	int32_t nRet;

	const int32_t nPtSize = 2;
	Point2Du_t arstPt[100] = { 0, };
	Point3Df_t arstGT3DPt[100] = { 0, };
	EVC_Data_t stEVC = { 0, };
	stEVC.VehLine = 167;
	stEVC.RoofStyle = 0;


	arstGT3DPt[0].x = 1.173;
	arstGT3DPt[0].y = -0.006;
	arstGT3DPt[0].z = 0.573;
	arstGT3DPt[1].x = 1.225;
	arstGT3DPt[1].y = 0.003;
	arstGT3DPt[1].z = 0.573;

	arstPt[0].u = 159;
	arstPt[0].v = 120;
	arstPt[1].u = 172;
	arstPt[1].v = 116;

	nRet = offline::ValidationOnlineCalibration("D:/Record/OnlineCalibration_TESTCASE/20180329_#2/normal with number2/2_normal.dat", "GTResult.txt", stEVC, arstPt, arstGT3DPt, nPtSize);
	//"D:/Record/OnlineCalibration_TESTCASE/20180329_#2/graragecar/1.dat"
}

void Example20_GenerateOnlineCalibration()
{
#ifdef _WIN32
	std::string strDir = ".\\TestFiles\\GenerateExtrinsic\\";
#else
	std::string strDir = "./TestFiles/GenerateExtrinsic/";
#endif

//	/* Duplicate test files to make 1024 additional test raw image files */
	std::list<std::string> listAmpImages;
	listAmpImages.push_back(strDir + "167_0223_2942514572_A_2018_03_28_17_00_47_0001030700.raw");
	listAmpImages.push_back(strDir + "167_0223_2942514572_A_2018_03_28_17_00_47_0001063898.raw");
	listAmpImages.push_back(strDir + "167_0223_2942514572_A_2018_03_28_17_00_47_0001097097.raw");
	listAmpImages.push_back(strDir + "167_0223_2942514572_A_2018_03_28_17_00_47_0001130295.raw");
	listAmpImages.push_back(strDir + "167_0223_2942514572_A_2018_03_28_17_00_47_0001163493.raw");
	listAmpImages.push_back(strDir + "167_0223_2942514572_A_2018_03_28_17_00_47_0001196692.raw");
	listAmpImages.push_back(strDir + "167_0223_2942514572_A_2018_03_28_17_00_47_0001229890.raw");
	listAmpImages.push_back(strDir + "167_0223_2942514572_A_2018_03_28_17_00_47_0001263088.raw");
	listAmpImages.push_back(strDir + "167_0223_2942514572_A_2018_03_28_17_00_47_0001296287.raw");
	listAmpImages.push_back(strDir + "167_0223_2942514572_A_2018_03_28_17_00_47_0001329485.raw");
	listAmpImages.push_back(strDir + "167_0223_2942514572_A_2018_03_28_17_00_47_0001362683.raw");
	listAmpImages.push_back(strDir + "167_0223_2942514572_A_2018_03_28_17_00_47_0001395882.raw");
	listAmpImages.push_back(strDir + "167_0223_2942514572_A_2018_03_28_17_00_47_0001429080.raw");
	listAmpImages.push_back(strDir + "167_0223_2942514572_A_2018_03_28_17_00_47_0001462278.raw");
	listAmpImages.push_back(strDir + "167_0223_2942514572_A_2018_03_28_17_00_47_0001495477.raw");
	listAmpImages.push_back(strDir + "167_0223_2942514572_A_2018_03_28_17_00_47_0001528675.raw");

	std::list<std::string> listDepthImages(listAmpImages);
	for (auto &i : listDepthImages) {
		i.replace(i.length() - 36, 1, "D");
	}

	std::list<std::string> newAmpImages(listAmpImages);
	std::list<std::string> newDepthImages(listDepthImages);

	auto CopyFiles = [](int i, std::list<std::string> &imageFiles, std::list <std::string> &newImageFiles) {
		char strTargetTimestamp[11];
		for (auto &j : imageFiles) {
			std::string strTarget = j;
			std::string strTimestamp = strTarget.substr(strTarget.length() - 14, 10);
			int nTimestamp = std::stoi(strTimestamp, nullptr, 10);

			sprintf(strTargetTimestamp, "%010d", nTimestamp + 5280000 * (i + 1));
			strTarget.replace(strTarget.length() - 14, 10, strTargetTimestamp);

#ifdef _WIN32
			if (CopyFileA(j.c_str(), strTarget.c_str(), FALSE) == 0) {
				printf("Failed to copy file : %s, %d\n", strTarget.c_str(), GetLastError());
				assert(false);
			}
#else //Linux
			int readFd;
			int writeFd;
			struct stat statBuf;
			std::string strErr;

			readFd = open(j.c_str(), O_RDONLY);
			if (readFd == -1) {
				strErr = "Failed to open raw file ";
				strErr += j;
				strErr += " ";

				perror(strErr.c_str());
				assert(false);
			}

			if (fstat(readFd, &statBuf) == -1) {
				strErr = "Failed to get status of file ";
				strErr += j;
				strErr += " ";

				perror(strErr.c_str());
				assert(false);
			}

			writeFd = open(strTarget.c_str(), O_WRONLY | O_CREAT, statBuf.st_mode);
			if (writeFd == -1) {
				strErr = "Failed to open target raw file ";
				strErr += strTarget;
				strErr += " ";

				perror(strErr.c_str());
				assert(false);
			}

			if (sendfile(writeFd, readFd, nullptr, statBuf.st_size) == -1) {
				strErr = "Failed to copy raw file ";
				strErr += strTarget;
				strErr += " ";

				perror(strErr.c_str());
				assert(false);
			}

			close(readFd);
			close(writeFd);
#endif
			newImageFiles.push_back(strTarget);
		}
	};

	for (int i = 0; i < 64; i++) {
		CopyFiles(i, listAmpImages, newAmpImages);
		CopyFiles(i, listDepthImages, newDepthImages);
	}

	/* Reset framecount to 0, then generate online calibration parameter files */
	EVC_Data_t stEVCInfo = { 0, };
	stEVCInfo.BodyStyle = 1; // 1 is V model
	stEVCInfo.RoofStyle = 7; // 0 : panorama, 1 : sunroof, 7:no roof
	stEVCInfo.VehLine = 167; // vehicle line
	stEVCInfo.StStyle = 1; // 1: LHD, 2:RHD

	int retCal = GenerateOnlineCalibration(strDir.c_str(), strDir.c_str(), (strDir + "omscal_intrinsic.bin").c_str(), strDir.c_str(), "../include/OnlineCalibration", stEVCInfo);

	/* Validate framecount */
	auto ValidateFramecount = [](std::list<std::string> &imageList, uint16_t indicator) {
		std::fstream file;
		uint16_t szHeader[2];
		uint16_t count = 0;

		for (auto &i : imageList) {
			file.open(i.c_str(), std::ios::in | std::ios::binary);
			assert(file.good());

			file.read(reinterpret_cast<char*>(szHeader), sizeof(szHeader));
			file.close();

			assert(szHeader[0] == indicator);
			assert(szHeader[1] == count);
			count += 1;
			count %= MAX_FRAMECOUNT;
		}
	};

	ValidateFramecount(newAmpImages, 0x0A2D);
	ValidateFramecount(newDepthImages, 0x0A3D);

	/* Validate return value of generated online calibration */
	assert(retCal == 0);
}

void Example21_TestGetUVInOtherCamera()
{
	ErrorType eRet1 = SUCCESS;
	ErrorType eRet2 = SUCCESS;
	
	uint16_t usOutU = 0;
	uint16_t usOutV = 0;
	uint16_t usInpU = 153;
	uint16_t usInpV = 23;
	float32_t fError1 = 0.f;
	float32_t fError2 = 0.f;

	std::vector<Point2Du_t> vInputPt;
	std::vector<Point2Du_t> vOutputPt;

	//Point2Du_t stPt[6] = { { 153, 23 }, { 122, 52 }, { 109, 75 }, { 115, 103 }, { 164, 138 }, {274, 69 } };// // matched pt (482,155) (512, 140), (532, 117) (536, 91) (498, 38) 372, 82
	Point2Du_t stPt[6] = { { 482, 155 }, { 512, 140 }, { 532, 117 }, { 536, 91 }, { 498, 38 }, { 372, 82 } };// // matched pt (482,155) (512, 140), (532, 117) (536, 91) (498, 38) 372, 82
	vInputPt.push_back(stPt[0]);
	vInputPt.push_back(stPt[1]);
	vInputPt.push_back(stPt[2]);
	vInputPt.push_back(stPt[3]);
	vInputPt.push_back(stPt[4]);
	vInputPt.push_back(stPt[5]);

	ErrorType retPP = offline::InitializePreProcessing_core((char *)"./TestFiles/FrontAPITest/", 2, APVersion::LATEST);
	if (retPP != SUCCESS)
	{
		printf("[OEC] Failed to initialize preprocessing\n");
		return;
	}

	uint16_t pusRightIR[SENSOR_HT_LIB * SENSOR_WD_LIB] = { 0, };
	uint16_t pusRightDepth[SENSOR_HT_LIB * SENSOR_WD_LIB] = { 0, };
	uint16_t pusLeftIR[SENSOR_HT_LIB * SENSOR_WD_LIB] = { 0, };
	uint16_t pusLeftDepth[SENSOR_HT_LIB * SENSOR_WD_LIB] = { 0, };

	LoadPNG("./TestFiles/FrontAPITest/LG_OA_02557.png", (char*)pusRightIR, sizeof(uint16_t) * SENSOR_HT_LIB * SENSOR_WD_LIB);
	LoadPNG("./TestFiles/FrontAPITest/LG_OR_02557.png", (char*)pusRightDepth, sizeof(uint16_t) * SENSOR_HT_LIB * SENSOR_WD_LIB);
	LoadPNG("./TestFiles/FrontAPITest/LG_OA_02249.png", (char*)pusLeftIR, sizeof(uint16_t) * SENSOR_HT_LIB * SENSOR_WD_LIB);
	LoadPNG("./TestFiles/FrontAPITest/LG_OR_02249.png", (char*)pusLeftDepth, sizeof(uint16_t) * SENSOR_HT_LIB * SENSOR_WD_LIB);
	
	eRet1 = offline::GetUVInOtherCamera(usInpU, usInpV, usOutU, usOutV, pusLeftIR, pusLeftDepth, pusRightIR, pusRightDepth, fError1, NULL, 0, eCameraPosition::FrontLeft);
	eRet2 = offline::GetUVInOtherCamera(&vInputPt, &vOutputPt, pusLeftIR, pusLeftDepth, pusRightIR, pusRightDepth, fError1, NULL, 0, eCameraPosition::FrontLeft);

	if (eRet1 != SUCCESS)
	{
		printf("GetUVInOtherCamera1 Return Error\n");
	}
	else
	{
		printf("\nExample21,1, Input: %d %d, Output:%d %d\n\n", usInpU, usInpV, usOutU, usOutV);
	}
	if (eRet2 != SUCCESS)
	{
		printf("GetUVInOtherCamera2 Return Error\n");
	}
	else
	{
		for (int32_t i = 0; i < vInputPt.size(); i++)
		{
			printf("Example21,2, Input: %d %d, Output:%d %d\n", vInputPt.at(i).u, vInputPt.at(i).v, vOutputPt.at(i).u, vOutputPt.at(i).v);
		}
	}
}



static void GetStats(uint16_t *img, int len, double *mean, double *variance)
{
	std::vector<uint16_t> v;
	double s, m, acc, var;	

	v.assign(img, img + len);
	s = std::accumulate(v.begin(), v.end(), 0.0);
	m = s / v.size();
	acc = 0.0;
	std::for_each (v.begin(), v.end(), [&](const double d) {
		acc += (d - m) * (d - m);
	});
	var = acc / (v.size() - 1);

	if (mean) *mean = m;
	if (variance) *variance = var;
}

static void assertInvalidResult(ErrorType ret, const std::vector<Point3Df_t> actual, int len)
{
	for (int i = 0; i < len; i++)
	{
		Point3Df_t p = actual[i];
		if (p.x == 0 && p.y == 0 && p.z == 0)
		{
			assert (ret != SUCCESS);
		}
		
	}
}

#ifdef WIN32
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	Example0_CalibrationFille_Format_Updated();
	Example0_1_InitializingFromEEPROMFormat();
	// PP on PS APIs
	// We don't support Entry R8 anymore. e.g) Preprocessing_core_PS
	/*
	Example1_preprocessing_core_PS();
	Example2_GetPointCloudArray_3d();
	Example9_ExportSensorPointAsPLY();
	Example10_Preprocessing_core_PS_elapsed_time();
	*/
	Example2_2_GetPointCloudArray_3d();
	// End of PP-on-PS

	// PP on PL APIs
	Example3_Preprocessing_core_PL();
	Example3_1_Preprocessing_core_PL_VGA();
	Example3_2_Preprocessing_core_PL_Flip();
	Example4_GetFilteredPointCloudPatch();
	Example4_2_GetFilteredPointCloudPatch_Filp();
	Example4_2_GetFilteredPointCloudPatch_Filp_MinModel();
	Example4_3_PointFilter();
	Example4_4_ExistsIn();

	// End of PP-on-PL

	Example5_LoadRaw();

	//Example6_repeatExampleItself_for_sanitycheck();
	Example7_Preprocessing_core_PL_goldenset_test();
	Example8_GetPixelXYPoint();

	Example9_ExportSensorPointAsPLY_Nilesh();
	Example11_Preprocessing_core_PL_elapsed_time();

	Example12_Preprocessing_core_PL_RegressionTest();

	Example13_GetInvalidMask();
	Example14_GetRTMatrix();
	Example15_GetPointCloudPatch_MinModel();
	Example16_GetHalfResize_core_MinModel();
	Example17_Preprocessing_core_PL_MinModel();

	// Online calibration test & validation APIs
#ifndef _WIN32
	Example18_OnlineCalibration_TestOperation();
	Example19_OnlineCalibration_Validation();
	Example20_GenerateOnlineCalibration();
#endif

	//GetUVInOtherCamera API Test
	Example21_TestGetUVInOtherCamera();
	return 0;
}

