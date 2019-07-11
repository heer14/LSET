/**
	@file	OfflineFilterSDK.h
	@brief
		Interface file for OfflineFilterSDK library.
	@details
		OfflineFilterSDK is used for offline testing of amplitude and depth images
		for preprocessing, bilateralfilter, geometric distancecorrection and CRC32.
		Library supports PNG, raw and pointer to amplitude and depth image buffers
		as input/output.
	@author	Adhipathi Reddy (adhipathi.reddy@lge.com)
	@date	2017-08-29
	@section LICENSE
		ADAS Engineering Division, Vehicle Components Company, LG Electronics
		COPYRIGHT(c) LGE CO.,LTD. 2017. SEOUL, KOREA.
		All rights are reserved.
		No part of this work covered by the copyright hereon may be
		reproduced, stored in a retrieval system, in any form or
		by any means, electronic, mechanical, photocopying, recording
		or otherwise, without the prior permission of LG Electronics.
*/
#ifndef _OFFLINE_FILTER_SDK_H
#define _OFFLINE_FILTER_SDK_H

#ifdef _WIN32
	#ifdef OFFLINEFILTERSDK_EXPORTS
		#define OFFLINEFILTERSDK_API __declspec(dllexport)
		#define	DLL_EXPORT			 __declspec(dllexport)
	#else
		#define OFFLINEFILTERSDK_API __declspec(dllimport)
		#define	DLL_EXPORT			 __declspec(dllimport)
	#endif
#else
	#define OFFLINEFILTERSDK_API
#endif

#include <list>
#include "PreProcessingCore.h"
#include "PreProcDefine.h"
#include "ThreeDLookUpAPICore.h"
#include "OnlineCalibration/ExtCalibration.h"
#include <list>

namespace offline {
	// actual value is meaningless. don't assume the value.
	enum APVersion {
		R11_3_2_2= 0x0B030202,
		MIN_R5_1_0_1 = 0x05010001,
		LATEST   = 0xFFFFFFFF,		// specifies the latest of Entry

		// below list of version will be removed in next release
		// Also, if you use the versions, you will be deprecated messages when InitializePreProcessing_core() and program will be terminated.
		R8_1_1_5 = 0x08010105,
		R8_1_2_3 = 0x08010203,

		R9_0_0_4 = 0x09000004,
		R9_0_0_5 = 0x09000005,
		R9_0_0_6 = 0x09000006,
		R9_0_0_8 = 0x09000008,
		R9_0_1_0 = 0x09000100,
		R10_0_1_0= 0x0A000100,
		R10_2_1_0= 0x0A020100,
		R10_4_0_3= 0x0A040003,
		R10_4_2_0= 0x0A040200,
		R10_4_3_1= 0x0A040301,
		MIN_R2_1 = 0x02010000
	};

	enum FlipKind {
		FLIP_NORMAL = 0,
		FLIP_VERTICAL = 1,
		FLIP_HORIZONTAL = 2,
		FLIP_BOTH = 3
	};

	// subset of PPStatus
	enum Status {
		OMS_FAIL = -21,
		CALIBRATION_FILE_FAIL = -3,
		NOT_INITIALIZED = -1,
		NORMAL = 0,
	};

	enum InvalidType {
		VALID = 0,
		OUT_OF_FOV = 1,
		UNRELIABLE = 2,
		UNAVAILABLE = 3,
		ABNORMAL_STATUS = 99
	};
	
	OFFLINEFILTERSDK_API extern const Point3Du_t AVAILABLE_POSITION_MIN;
	OFFLINEFILTERSDK_API extern const Point3Du_t AVAILABLE_POSITION_MAX;

	/////////////////////////////////////////////////////////
	// PreProcesingCore API
	/**
	@brief Intialized for preprocessing & ThreeDLookUpAPI(Point Cloud)
	@param pszCorrTablePath: geometric distance correction table file "vr2/omscal_table.bin"
	@param pszIntrinsicPath: camera intrinsic parameter file "vr2/omscal_intrinsic.bin"
	*/
	OFFLINEFILTERSDK_API ErrorType InitializePreProcessing_core(char* pszCorrTablePath, char* pszIntrinsicPath);

	/**
	@brief Intialized for preprocessing & ThreeDLookUpAPI(Point Cloud)
	@param pszCalibrationDirectory: calibration parameter directory ends with '/'. That should contains omscal_table.in omscal_intrinsic.bin, omscal_offset.bin
	@param APVersion: target ApplicationProcessor S/W version for simulating Preprocessing_core_PS, Preprocessing_core_PL
	*/
	OFFLINEFILTERSDK_API ErrorType InitializePreProcessing_core(char* pszCalibrationDirectory, APVersion version = offline::LATEST);

	/**
	@brief Intialized for preprocessing & ThreeDLookUpAPI(Point Cloud)
	@param pszCalibrationDirectory: calibration parameter directory ends with '/'. That should contains omscal_table.in omscal_intrinsic.bin, omscal_offset.bin
	@param nCameras: the number of cameras
	@param APVersion: target ApplicationProcessor S/W version for simulating Preprocessing_core_PS, Preprocessing_core_PL
	*/
	OFFLINEFILTERSDK_API ErrorType InitializePreProcessing_core(char* pszCalibrationDirectory, uint32_t nCameras, APVersion version = offline::LATEST);

	/**
	@brief Simulate preprocessing on PS(ARM core). It requires VGA sized frame and results in VGA sized frame.
	@param pusInDepth[in]: start pointer of depth image
	@param pusOutDepth[out]: start pointer of depth image
	@param pusInIR[in]: start pointer of IR image
	*/
	OFFLINEFILTERSDK_API ErrorType Preprocessing_core_PS(pImgPixel pusInDepth, pImgPixel pusOutDepth, pImgPixel pusResIR, uint32_t iCameraIndex = 0);

	/**
	@brief Simulate preprocessing on PL(programmable logic). It requires VGA sized frame and results in QVGA sized frame.
	@param pusInDepth[in]: start pointer of depth image
	@param pusOutDepth[out]: start pointer of depth image
	@param pusInIR[in]: start pointer of IR image
	@param pusResizeIR[out]: start pointer of IR image
	*/
	OFFLINEFILTERSDK_API int32_t Preprocessing_core_PL(pImgPixel pusInDepth, pImgPixel pusOutDepth, pImgPixel pusResIR, pImgPixel pusResizeIR, uint32_t iCameraIndex = 0);

	/**
	@brief Simulate preprocessing on PL(programmable logic). It avoids scaling of the frame.
	@param pusInDepth[in]: start pointer of depth image
	@param pusOutDepth[out]: start pointer of depth image
	@param pusInIR[in]: start pointer of IR image
	@param pusResizeIR[out]: start pointer of IR image
	*/
	OFFLINEFILTERSDK_API int32_t Preprocessing_core_PL_VGA(pImgPixel pusInDepth, pImgPixel pusOutDepth, pImgPixel pusResIR, pImgPixel pusResizeIR, uint32_t iCameraIndex = 0);

	/**
	@brief Get QVGA sized image from VGA size
	@param pusIn[in]: start pointer of depth image
	@param pusOut[out]: start pointer of depth image
	@param pusInIR[in]: start pointer of IR image
	@param pusOutIR[out]: start pointer of IR image output
	@return 0 if success. non-zero otherwise.
	*/
	OFFLINEFILTERSDK_API int32_t GetHalfResize_core(pImgPixel pusIn, pImgPixel pusOut, pImgPixel pusInIR, pImgPixel pusOutIR);

	/**
	@brief Get point cloud in patch region of filtered image
	@param pusIn : Preprocessed 3D (u,v,r) image buffer
	@parma parWorldPoint : result world (x,y,z) array
	@parma patch_y: y coordinate in upper left corner of patch in 3D image
	@parma patch_x: x coordinate in upper left corner of patch in 3D image
	@parma patch_height: patch height
	@parma patch_width: patch width
	@param pfRT : rotation translation matrix (3x4)
	@param wd : image width (320 or 640)
	@param ht : image height (240 or 480)
	@param usMin  : minimum distance(mili meter) ( if depth <= usMIn then x=y=z=0)
	@param usMax  : maximum distance (mili meter) ( if depth >= usMax then x=y=z=0)
	@return value (0)SUCCESS other Error Code
	*/
	OFFLINEFILTERSDK_API ErrorType GetFilteredPointCloudPatch(uint16_t *pusDepth, uint16_t * pusIR, std::vector<Point3Df_t>* parWorldPoint, uint16_t patch_y, uint16_t patch_x, uint16_t patch_height, uint16_t patch_width, float32_t* pfRT, int32_t wd, int32_t ht, uint16_t usMin, uint16_t usMax, int32_t iCameraIndex = 0);

	OFFLINEFILTERSDK_API ErrorType GetFilteredPointCloudPatch(uint16_t *pusDepth, uint16_t * pusIR, std::vector<Point3Df_t>* parWorldPoint, uint16_t patch_y, uint16_t patch_x, uint16_t patch_height, uint16_t patch_width, float32_t* pfRT, CameraPosition_t eCameraPosition = eCameraPosition::Entry);
	/**
	@brief Get point cloud from 3D point array
	@param parImagePoint : Preprocessed 3D (u,v,r) image coordinate array for point cloud
	@parma parWorldPoint : result world (x,y,z) array
	@param pfRT : rotation translation matrix (3x4)
	@param wd : image width (320 or 640)
	@param ht : image height (240 or 480)
	@param usMin  : minimum distance(mili meter) ( if depth <= usMIn then x=y=z=0)
	@param usMax  : maximum distance (mili meter) ( if depth >= usMax then x=y=z=0)
	@return value (0)SUCCESS other Error Code
	*/
	OFFLINEFILTERSDK_API ErrorType GetPointCloudArray_3d(std::vector<Point3Du_t>* parImagePoint, std::vector<Point3Df_t>* parWorldPoint, float32_t* pfRT, int32_t wd, int32_t ht, uint16_t usMin, uint16_t usMax, int32_t iCameraindex);

	/**
	@brief filter patch regions and return filtered depth values specified in `arImagePoints`
	@details Image should be QVGA. e.g) pixels(`pInDepth`) = 320 x 240. 
	@param pInDepth[in]: start pointer of depth image
	@parma pInIR[in]: start pointer of IR image
	@param arImagePoints[in]: vector of center point of patch
	@param patch_height[in]: height of patch
	@param patch_width[in]: width of patch
	@param iCameraIndex[in]: camera device ID which is starting 0
	@return filtered depth values specified in `arImagePoints`, otherwise empty vector
	*/
	OFFLINEFILTERSDK_API std::vector<uint16_t> PointFilter(pImgPixel pInDepth, pImgPixel pInIR, std::vector<Point3Du_t> &arImagePoints, uint16_t patch_height, uint16_t patch_width, int32_t iCameraindex = 0);

	/**
	@brief [OMS-HIGH] Get error status
	@return Status which specifies calibration loading was success or not.
	*/
	OFFLINEFILTERSDK_API Status GetStatus();

	/**
	@brief [OMS-HIGH] Set RHD flag
	@details It affects 3d look up result such as `GetFilteredPointCloudPatch(). By default, it is set to false in internal.
	@param value[in]: set Right Side Driver
	@return void
	*/
	OFFLINEFILTERSDK_API void SetRHD(bool value);

	/**
	@brief [OMS-HIGH] chekc whether RHD flag is set or not.
	@details It affects 3d look up result such as `GetFilteredPointCloudPatch().
	@param value[in]: true if Right Side Driver.
	@return true is RHD flag is set, Otherwise false.
	*/
	OFFLINEFILTERSDK_API bool IsRHD();

	OFFLINEFILTERSDK_API InvalidType isAvailable(int32_t u, int32_t v, CameraPosition_t pos);
	/**--------------------------------------------------------------------

	Configuration API (DO NOT USE THESE APIs IF ANY SPECIAL REASON)

	---------------------------------------------------------------------*/

	/**
	 * @brief enable or diable temperature compensation
	 * @param (INPUT) enable : true if enable temperature compensation, false otherwise.
	 */
	OFFLINEFILTERSDK_API void EnableTemperatureCompensation(bool enable);
	/**
	 * @brief check whether temperature compensation is enabled or not
	 * @return true if temperature compensation enabled, false otherwise
	 */
	OFFLINEFILTERSDK_API bool IsTemperatureCompensationEnabled();

	/**--------------------------------------------------------------------

	Utilities

	---------------------------------------------------------------------*/

	/**
	 * @brief get RT matrix from extrins_file
	 * @param (INPUT) extrinsic_file: extrinsic file path which extracted from logging data
	 * @param (OUTPUT) pfRT: rotation and translation matrix result
	 * @return true if success, false otherwise
	 */
	OFFLINEFILTERSDK_API bool GetRTMatrix(const char *extrinsic_file, float32_t pfRT[12]);

	/**
	 * @brief Get the cloud point information of the particular point(x,y) in the Distorted image
	 * @param (INPUT) X, Y, Z is the cloud point information at Vehicle coordinate, if pRT is default , X,Y,Z is camera coordinate
	 * @param (OUTPUT) x and y refers to distance value at that point in the original image(VGA)
# coordinate default camera pRT = (1,0,0,0 ,0,1,0,0, 0,0,1,0}
	 * @param iCameraindex is index of camera.
	 * @return true if cloud points are valid, false otherwise
	 */
	OFFLINEFILTERSDK_API bool GetPixelXY(float32_t X, float32_t Y, float32_t Z, float32_t &x, float32_t &y, float32_t* pfRT, int32_t iCameraindex);

	/**
	 * @brief  save sensor points in a PLY file (e.g. to visualize with MeshLab)
	 * @param parPoint3D : array point cloud that consist of x,y,z (mm), R,G,B (color)
	 * @param resFilename : pointer to a text buffer of size sLen, if not NULL: resFilename returns the filename of the PLY file
	 * @return true value  : error code
	 */
	OFFLINEFILTERSDK_API ErrorType ExportSensorPointsAsPLY(std::vector<Point3D_t>* parPoint3D, char_t *resFilename);

	/**
	 * @brief  save sensor points in a PLY file (e.g. to visualize with MeshLab)
	 * @param z: z in coordinate x,y,z
	 * @param range: the maximum value `z`
	 * @param (output) r: r of RGB
	 * @param (output) g: g of RGB
	 * @param (output) b: b of RGB
	 */
	OFFLINEFILTERSDK_API void ColorDepthPixel_3d(float32_t z, float32_t range, uint8_t &r, uint8_t &g, uint8_t &b);

	/**
	// @brief Load raw files into `buffer`
	//@param rawFile: .raw file path
	//@parma buffer: points to buffer to be loaded
	//@param bytes: buffer size
	//return value (0)SUCCESS, (-1) Open error, Otherwise written bytes
	*/
	OFFLINEFILTERSDK_API int LoadRaw(const char *rawFile, char *buffer, int bytes);
	OFFLINEFILTERSDK_API int LoadRaw(const std::string &rawFile, char *buffer, int bytes);

	/**
	// @brief Load png files into `buffer`
	//@param pngFile: .png file path
	//@parma buffer: points to buffer to be loaded
	//@param bytes: buffer size
	//return value (0)SUCCESS otherwise -1
	*/
	OFFLINEFILTERSDK_API int LoadPNG(const char *pngFile, char *buffer, int bytes);

	/**
	// @brief save `buffer` into `outFile` as binary. any contents that existed in the file
	// before it is open are discarded.
	//@param outFile: .raw output file path
	//@parma buffer: points to buffer to save
	//@param bytes: buffer size
	//return value (0)SUCCESS otherwise -1
	*/
	OFFLINEFILTERSDK_API int SaveRaw(const char *outFile, char *buffer, int bytes);
	OFFLINEFILTERSDK_API int SaveRaw(const std::string &outFile, char *buffer, int bytes);

	/**
	@brief Get camera parameter. It is only used for using dump internal state in test
	@param iCameraIndex: camera index
	*/
	OFFLINEFILTERSDK_API PreprocessorParams* GetCameraParam(int32_t iCameraIndex = 0);

	/**
	@brief Return Invalid area mask
	@details Each element specifies the corresponding pixel and invalid if 0.
	@param pos[in]: Target camera position(index)
	@param tp[in]: invalid type to check. default = OUT_OF_FOV
	@return : 640x480 image array. invalid pixels are set to 1. valid pixels are 0
	*/
	OFFLINEFILTERSDK_API std::vector<uint16_t> GetInvalidMask(CameraPosition_t pos, InvalidType tp = OUT_OF_FOV);

	/**
	@brief Online Calibration Test Operation Function
	@details This test load raw data, intrinsic data, extrinsic data from Dat file. And then, this test check online calibration service operation
	@param datFile: dat file path
	@param nVehicleInfo: vehicle line number
	@param nIRViewGain: viewer ir gain
	return value (0)SUCCESS, (-22) dat Open error,
	*/
	OFFLINEFILTERSDK_API int TestOnlineCalibration(const char *datFile, int32_t nVehicleInfo, int32_t nIRViewGain, int32_t iCameraIndex = 0);

	/**
	@brief Online Calibration Validation
	@details This test load raw data, intrinsic data, extrinsic data from Dat file. And then this test evaluate patch xyz accuracy.
	@param datFile: dat file path
	@param ResultFile: result file path
	@param stEVC: evc information
	@param pstPt: patch u,v position
	@param pstGT3d: ground truth x,y,z position
	@param nPtSize: patch size
	return value (0)SUCCESS, (-22) dat Open error,
	*/
	OFFLINEFILTERSDK_API int ValidationOnlineCalibration(const char *datFile, const char *ResultFile, EVC_Data_t stEVC, Point2Du_t *pstPt, Point3Df_t *pstGT3d, int32_t nPtSize, int32_t iCameraIndex = 0);


	/**
	@brief Generate online calibration paramter files
	@details This function generates online calibration paramter files(omscal_extrinsic_TIMESTAMP.bin) from given images files(e.g. Extracted DAT file from ImageExtractor)
			 Before generating, framecount in all images are reset from 0
	@param irPath: Path of IR image
	@param irDepth: Path of depth image
	@param intrinsicPath: Path of intrinsic parameter file(omscal_intrinsic.bin)
	@param outputPath: Path of output files
	@param vehicleinfo: vehicle information
	return value (0)SUCCESS, otherwise -1
	*/
	OFFLINEFILTERSDK_API int GenerateOnlineCalibration(const char *irPath, const char *depthPath, const char *intrinsicPath, const char *outputPath, const char *binary_path, EVC_Data_t vehicleinfo);

	/**
	@brief Generate Extrinsic Result Core Function
	@details This test load raw data, intrinsic data. And then, this function genrate new extrinsic result in extrinsic_path
	@param arstImageList: image list
	@param intrinsic_path: input intrinsic path
	@param nVehicleInfo: vehicle line number
	@param extrinsic_path: folder path of generated extrinsic result
	return value (0)SUCCESS, (-22) dat Open error,
	*/
	OFFLINEFILTERSDK_API ErrorType GenerateExrinsicCore(std::list<std::string> &arstImageList, const char *intrinsic_path, EVC_Data_t nVehicleInfo, const char *extrinsic_path, const char *binary_path, int32_t iCameraIndex = 0);
	/**
	@brief Set flip mode
	@details it affects the result of offline::Preprocessing_core_PL, GetFilteredPointCloudPatch and GetPointCloudArray_3d.
                 For example, Preprocessing_core_PL produces output with the input flipped vertically if SetFilpMode was called with FLIP_VERTICAL.
                 Likewise, GetFilteredPointCloudPatch produces world coordinate points with the input flipped vertically.
	@param mode: FLIP_VERTICAL, FLIP_HORIZONTAL, FLIP_BOTH. FLIP_NORMAL means no flip.
	return 
	*/
	OFFLINEFILTERSDK_API void SetFlipMode(FlipKind mode);

	/**
	@brief Set flip mode
	@details See SetFlipMode(FlipKind mode)
	@param mode: 1 for vertical, 2 for horizontal, 3 for vertical and horizontal flip. 0 do nothing.
	return 
	*/
	OFFLINEFILTERSDK_API void SetFlipMode(int32_t mode);

	/**
	@brief it determines whether `point` is valid or not.
	@details When either `point.r` is zero or `point` is out of range, it return true
	@param point: point in u,v image coordinate
	@param isQVGA: true if `point` is in QVGA, false if `point` is in VGA sized image.
	return validity of `p`
	*/
	OFFLINEFILTERSDK_API bool IsInvalidPoint(Point3Du_t point, bool isQVGA = true);
	OFFLINEFILTERSDK_API bool IsInvalidPoint(std::vector<Point3Du_t> &points, bool isQVGA = true);

	/**
	 * @brief check whether projected world coordinate `point` is in `lower` and `upper` range.
	 * @param (INPUT) point is the cloud point which rotated and shifted by `pfRT` from camera coordinate.
	 * @param (INPUT) pfRT  : axis coordinate convert matrix ( 3x3 = 9 float32_t size) , include car coordinate convert(add 3x1: translate) --> (3x4: 12 float32_t size)
	 * @param (INPUT) lower is minimum image point and distance
	 * @param (INPUT) upper is maximum image point and distance 
	 * @param (INPUT) iCameraindex is index of camera.
	 * @return true if the range between `lower` and `upper` contains `point`
	 */
	OFFLINEFILTERSDK_API bool ContainsPointCloud(Point3Df_t point, float *pfRT, Point3Du_t clip_min = offline::AVAILABLE_POSITION_MIN, Point3Du_t clip_max = offline::AVAILABLE_POSITION_MAX, int32_t iCameraIndex = 0);

	/**
	* @brief get corresponding u',v',d' from current camera u,v,d about overlap region
	* @param input_u : input image u position
	* @param input_v : input image v position
	* @param output_u : corresponding u position
	* @param output_v : corresponding v position
	* @param pusLeftIR : left ir image
	* @param pusLeftDepth : preprocessed depth image pointer
	* @param pusRightIR : right ir image
	* @param pusRightDepth : preprocessed depth image pointer
	* @param fError : world coordinate difference between calculated xyz from other camera and calculated xyz from target camera
	* @param pfRelativeRT : relative extrinsic calibration. If you insert NULL, API use defined RT
	* @param ucImageType : 0 is VGA, 1 is QVGA
	* @param eTargetCameraPos : the camera looking for u,v coordinates.
	* @return 0 is success, -1 is fail
	*/
	OFFLINEFILTERSDK_API ErrorType GetUVInOtherCamera(uint16_t input_u, uint16_t input_v, uint16_t &output_u, uint16_t &output_v, uint16_t* pusLeftIR, uint16_t *pusLeftDepth,
		uint16_t* pusRightIR, uint16_t *pusRightDepth, float32_t &fError, float32_t *pfRelativeRT, uint8_t ucImageType, CameraPosition_t eTargetCameraPos);
	OFFLINEFILTERSDK_API ErrorType GetUVInOtherCamera(std::vector<Point2Du_t>* parInputPt, std::vector<Point2Du_t>* parOutputPt, uint16_t* pusLeftIR, uint16_t *pusLeftDepth,
		uint16_t* pusRightIR, uint16_t *pusRightDepth, float32_t &fError, float32_t *pfRelativeRT, uint8_t ucImageType, CameraPosition_t eTargetCameraPos);


	OFFLINEFILTERSDK_API Filter_Initialize_Param_t* GetFilterParams();
	/**
	* @brief find chessboard corner and calculte radial distance
	* @param pstIntPath : intrinsic calibration file path
	* @param stChess : chessboard setup data
	* @param pcGTPath : ground truth file path for functionB
	* @param pstEVC : EVC information
	* @return 0 is success, -1 is fail
	*/
	OFFLINEFILTERSDK_API ErrorType OnCalValidationInitialize(char_t *pstIntPath, ChessBoard_Input_t stChess, char_t *pcGTPath, char_t *pcMasterPath, int32_t nImageWidth, int32_t nImageHeight, EVC_Data_t *pstEVC, int32_t nCameraNum);
	/**
	* @brief find chessboard corner and calculte radial distance
	* @param pusIr : ir image
	* @param pusDepth : depth image
	* @param unrstCornerPt : found chessboard corner u,v point
	* @param frstGT : radial distance from chessboard extrinsic
	* @param fCenterdepth : radial distance from depth image
	* @return 0 is success, -1 is fail
	*/
	OFFLINEFILTERSDK_API ErrorType OnCalValidationFunctionA(uint16_t *pusIr, uint16_t *pusDepth, float32_t *unrstCornerPt, float32_t &frstGT, float32_t &fCenterdepth, int32_t iCameraindex = 0);
	/**
	* @brief compare hand position xyz with ground truth xyz
	* @param stInputPt : hand position x,y,z from omsalgo
	* @param pstOutput : output data
	* @return 0 is success, -1 is fail
	*/
	OFFLINEFILTERSDK_API ErrorType OnCalValidationFunctionB(Point3Df_t stInputPt, OnCal_Validation_OutputB_t *pstOutput, int32_t iCameraindex = 0);
	/**
	* @brief draw cad point based on online calibration result
	* @param pfRT : online calibration result 3x4 array
	* @param pfOutput : cad uv point( 2xN )
	* @param nNumPt : the number of cad UV Points
	* @return 0 is success, -1 is fail
	*/
	OFFLINEFILTERSDK_API ErrorType OnCalValidationFunctionC(float32_t *pfRT, float32_t *pfOutput, int32_t &nNumPt, int32_t iCameraindex = 0);
}


/**
@brief		Caculates CRC32 of the image
@details	Caculates CRC32 of the raw image pointed by buffer
@param 		buffer: pointer to image buffer for getting CRC32
@param 		buffer size in bytes
@return		CRC32 value of the image pointed by buffer
*/
OFFLINEFILTERSDK_API uint32_t getCRC32(const void *buffer, uint32_t bytes);


#endif //#define _OFFLINE_FILTER_SDK_H
