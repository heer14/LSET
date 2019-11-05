import os
import ctypes
import shutil
import re
import time
from PIL import Image
import numpy as np
import math
import sys
from pathlib import Path
import getpass
import argparse 
import csv
import glob
#created classes
from Include import ImageExtractor
from Include import OfflineFilterSDK
from Include import ImageCompare
from Config import config as cfg
from Include import Image_ReportGenerator as ReportGenerator
from Include import CSV_ReportGenerator


#2D
dict_raw_2d = { }
dict_raw_2d_1 = { }
dict_PP_2d = {}
dict_PP_2d_1 = {}

#3D        
dict_raw_3d = {}
dict_raw_3d_1 = {}

#preprocessing only on 3d
dict_test_3d = {}
dict_test_3d_1 = {}
dict_PP_3d = {}
dict_PP_3d_1 = {}

#for csv compare
xyzdata = { }

def getFrameCount(preprocessing) :
    image11 = np.zeros((cfg.width , cfg.height) ,dtype=np.uint16 )
    #get hex values 2D   
    #entry
    if(cfg.version == 1) :
        #print(cfg.path_raw_A)
        #print(cfg.path_raw_D)
        #print(cfg.path_test_3D)
        for image1 in os.listdir(cfg.path_raw_A ) :
            path1 = cfg.path_raw_A + image1
            ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
            if not image11[0][1] in dict_raw_2d:
                dict_raw_2d[image11[0][1]] = image1
                
            else :
                print("removing as duplicate frame count : "+ image1 )
    
        for image1 in os.listdir(cfg.path_raw_D ) :
            path1 = cfg.path_raw_D + image1
            ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
            if not image11[0][1] in dict_raw_3d:
                dict_raw_3d[image11[0][1]] = image1
            else :
                print("removing as duplicate frame count : "+ image1 )
        
        for image1 in os.listdir(cfg.path_test_3D) :
            path1 = cfg.path_test_3D+image1
            ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
            if not image11[0][1] in dict_test_3d:
                dict_test_3d[image11[0][1]] = image1
            else :
                print("removing as duplicate frame count : "+ image1 )
    
    
    #min
    elif(cfg.version == 2) :


        for image1 in os.listdir(cfg.path_raw_D+"Cam0\\") :
            path1 = cfg.path_raw_D+"Cam0\\" + image1
            ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
            if not image11[0][1] in dict_raw_3d:
                dict_raw_3d[image11[0][1]] = image1
                #print(image11[0][1])
                #print(" "+dict_raw_3d[image11[0][1]])
            else :
                print("removing as duplicate frame count : "+ image1 )

        for image1 in os.listdir(cfg.path_raw_D+"Cam1\\") :
            path1 = cfg.path_raw_D+"Cam1\\" + image1
            ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
            if not image11[0][1] in dict_raw_3d_1:
                dict_raw_3d_1[image11[0][1]] = image1
            else :
                print("removing as duplicate frame count : "+ image1 )

        for image1 in os.listdir(cfg.path_raw_A+"Cam0\\") :
            path1 = cfg.path_raw_A+"Cam0\\" + image1
            ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
            if not image11[0][1] in dict_raw_2d:
                dict_raw_2d[image11[0][1]] = image1
            else :
                print("removing as duplicate frame count : "+ image1 )

        for image1 in os.listdir(cfg.path_raw_A+"Cam1\\") :
            path1 = cfg.path_raw_A+"Cam1\\" + image1
            ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
            if not image11[0][1] in dict_raw_2d_1:
                dict_raw_2d_1[image11[0][1]] = image1
            else :
                print("removing as duplicate frame count : "+ image1 )
    
        for image1 in os.listdir(cfg.path_test_3D+"PP_3D\\") :
            path1 = cfg.path_test_3D+"PP_3D\\" + image1
            ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
            if not image11[0][1] in dict_test_3d:
                dict_test_3d[image11[0][1]] = image1
            else :
                print("removing as duplicate frame count : "+ image1 )

        for image1 in os.listdir(cfg.path_test_3D+"PP1_3D\\") :
            path1 = cfg.path_test_3D+"PP1_3D\\" + image1
            ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
            if not image11[0][1] in dict_test_3d_1:
                dict_test_3d_1[image11[0][1]] = image1
            else :
                print("removing as duplicate frame count : "+ image1 )


       

def getuser() :
    return getpass.getuser()

def MakeDir(path_) :
    output_dir = Path(path_).resolve()
    if output_dir.exists() :
        shutil.rmtree(path_)
    os.mkdir(path_)

def Compare_Images_FC_Entry(preprocessing) :
    

#init xls report
    Report_path = Path(cfg.Report_path).resolve()
    if not Report_path.exists() : 
        os.mkdir(cfg.Report_path)
    dat_file = os.path.basename(cfg.input_dat_path) 
    xlReport = ReportGenerator.ReportGenerator(  dat_file , cfg.path_test_2D , cfg.path_test_3D , getuser() , cfg.TOLERANCE_DIFF_PIXELS , "Entry" , cfg.TOLERANCE_PIXEL_WISE_DIFF , cfg.TOLERANCE_DIFF_PIXELS )
    xlReport.set_workbook_path(cfg.Report_path+cfg.Report_Image_Compare)
    localtime = time.asctime( time.localtime(time.time()) )
    xlReport.init_workbook(localtime)

    image11 = np.zeros((cfg.width , cfg.height) ,dtype=np.uint16 )
    image21 = np.zeros((cfg.width , cfg.height) ,dtype=np.uint16 )
    ImgComp = ImageCompare.ImageCompare()
 



# compare Images 3D 
    #print(len(dict_PP_3d))
    #print(len(dict_test_3d))
    for hex_PP in dict_PP_3d :
        f = 0
        for hex_test in dict_test_3d : 
            if (hex_test == hex_PP) :
                path1 = cfg.path_test_3D + dict_test_3d[hex_test]
                path2 = cfg.path_PP_D + dict_PP_3d[hex_PP]
                ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
                if not ( ret == 0 ):
                    sys.exit("Error in loading test images(2D) ! please check OMS Version (use -ov to provide  correct OMS version )")
                ret = preprocessing.LoadRaw(bytes(path2, 'utf-8'),image21.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
                if not ( ret == 0 ):
                    sys.exit("Error in loading PP images(2D) ! please check OMS Version (use -ov to provide  correct OMS version )")
                ret = ImgComp.bit_by_bit(image11 , image21 , cfg.height , cfg.width )
                pat = re.search(r"(\d{4}_\d{2}_\d{2}_\d{2}_\d{2}_\d{2}_\d{10})",dict_raw_3d[hex_PP])
                xlReport.add_data("3D" , dict_test_3d[hex_test] , dict_PP_3d[hex_PP] , pat.group(1) ,  hex_test , ret[0] , ret[1] )
                f = 1
                break
        if(f == 0) :
            xlReport.add_data("3D" , "N/A" , dict_PP_3d[hex_PP] , "N/A" ,  hex_PP , "Frame NOT Found" , "N/A" )
    
    xlReport.close()


def Compare_Images_FC_Min(preprocessing) :
    

#init xls report
    Report_path = Path(cfg.Report_path).resolve()
    if not Report_path.exists() : 
        os.mkdir(cfg.Report_path)
    dat_file = os.path.basename(cfg.input_dat_path) 
    xlReport = ReportGenerator.ReportGenerator(  dat_file , cfg.path_test_2D , cfg.path_test_3D , getuser() , cfg.TOLERANCE_DIFF_PIXELS , "Min" , cfg.TOLERANCE_PIXEL_WISE_DIFF , cfg.TOLERANCE_DIFF_PIXELS )
    xlReport.set_workbook_path(cfg.Report_path+cfg.Report_Image_Compare)
    localtime = time.asctime( time.localtime(time.time()) )
    xlReport.init_workbook(localtime)

    image11 = np.zeros((cfg.width , cfg.height) ,dtype=np.uint16 )
    image21 = np.zeros((cfg.width , cfg.height) ,dtype=np.uint16 )
    ImgComp = ImageCompare.ImageCompare()

    test_cam0 = cfg.path_test_3D+"PP_3D\\"
    test_cam1 = cfg.path_test_3D+"PP1_3D\\"
    PP_cam0 = cfg.path_PP_D+"Cam0\\"
    PP_cam1 = cfg.path_PP_D+"Cam1\\"

    

# compare Images 3D cam 0

    for hex_PP in dict_PP_3d :
        f = 0
        for hex_test in dict_test_3d : 
            if (hex_test == hex_PP) :
                path1 = test_cam0 + dict_test_3d[hex_test]
                path2 = PP_cam0 + dict_PP_3d[hex_PP]
                ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
                if not ( ret == 0 ):
                    sys.exit("Error in loading test images(3D) ! please check OMS Version (use -ov to provide  correct OMS version )")
                ret = preprocessing.LoadRaw(bytes(path2, 'utf-8'),image21.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
                if not ( ret == 0 ):
                    sys.exit("Error in loading PP images(3D) ! please check OMS Version (use -ov to provide  correct OMS version )")
                ret = ImgComp.bit_by_bit(image11 , image21 , cfg.height , cfg.width )
                pat = re.search(r"(\d{4}_\d{2}_\d{2}_\d{2}_\d{2}_\d{2}_\d{10})",dict_raw_3d[hex_PP])
                xlReport.add_data("3D" , dict_test_3d[hex_test] , dict_PP_3d[hex_PP] , pat.group(1) ,  hex_test , ret[0] , ret[1] )
                f = 1
                break
        if(f == 0) :
            xlReport.add_data("3D" , "N/A" , dict_PP_3d[hex_PP] , "N/A" ,  hex_PP , "Frame NOT Found" , "N/A" )
    
    
    for hex_PP in dict_PP_3d_1 :
        f = 0
        for hex_test in dict_test_3d_1 : 
            if (hex_test == hex_PP) :
                path1 = test_cam1 + dict_test_3d_1[hex_test]
                path2 = PP_cam1 + dict_PP_3d_1[hex_PP]
                ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
                if not ( ret == 0 ):
                    sys.exit("Error in loading test images(3D) ! please check OMS Version (use -ov to provide  correct OMS version )")
                ret = preprocessing.LoadRaw(bytes(path2, 'utf-8'),image21.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
                if not ( ret == 0 ):
                    sys.exit("Error in loading PP images(3D) ! please check OMS Version (use -ov to provide  correct OMS version )")
                ret = ImgComp.bit_by_bit(image11 , image21 , cfg.height , cfg.width )
                pat = re.search(r"(\d{4}_\d{2}_\d{2}_\d{2}_\d{2}_\d{2}_\d{10})",dict_raw_3d_1[hex_PP])
                xlReport.add_data("3D1" , dict_test_3d_1[hex_test] , dict_PP_3d_1[hex_PP] , pat.group(1) ,  hex_test , ret[0] , ret[1] )
                f = 1
                break
        if(f == 0) :
            xlReport.add_data("3D1" , "N/A" , dict_PP_3d_1[hex_PP] , "N/A" ,  hex_PP , "Frame NOT Found" , "N/A" )


    
    xlReport.close()

def Create_Dynamic_Path(path_updated) :

    cfg.Report_path = path_updated+"\\"
    cfg.path_PP = path_updated + cfg.path_PP
    cfg.path_PP_A = path_updated + cfg.path_PP_A
    cfg.path_PP_D = path_updated + cfg.path_PP_D
    cfg.path_raw = path_updated + cfg.path_raw
    cfg.path_raw_A = path_updated + cfg.path_raw_A
    cfg.path_raw_D = path_updated + cfg.path_raw_D
    cfg.path_to_Bin = path_updated + cfg.path_to_Bin
    cfg.path_to_calib = path_updated + cfg.path_to_calib

def Extract_Images() : 
    print("Extracting Images")
    path1 = Path(cfg.Unprocessed_raw_Images).resolve()
    if not path1.exists() :
        os.mkdir(cfg.Unprocessed_raw_Images)

    imgExt = ImageExtractor.ImageExtractor(cfg.input_dat_path ,cfg.image_extractor_path , cfg.Unprocessed_raw_Images )
    imgExt.Extract_Dat_info()
    (ret , pathD ) = imgExt.Resolve()
    if (ret == 1) :
        sys.exit('Please set correct path of input DAT file(' + str(cfg.input_dat_path) + ')')
    elif (ret == 2) : 
        sys.exit('Please set correct path of ImageExtractor(' + str(cfg.image_extractor_path) + ')')
    elif (ret == 3) :
        sys.exit('Please set correct path of output directory(' + str(cfg.Unprocessed_raw_Images) + ')')
    else :
        Create_Dynamic_Path(pathD )
        
        ret = imgExt.Run()
        
        if ret.returncode == 0:
            print('Image extractor : Success')
        else : 
            sys.exit('Image extractor : Fail') 
        
        
      
           
def Separate_Raw_Image_Entry() : 
    print("separating  2D and 3D Images")
    MakeDir(cfg.path_raw_A)
    MakeDir(cfg.path_raw_D)
    for file in os.listdir(cfg.path_raw) :
        if file.endswith(".raw") :
            oldPath = cfg.path_raw + file
            if "_A_" in file :
                shutil.copy(oldPath , cfg.path_raw_A )
            elif "_D_" in file :
                shutil.copy(oldPath , cfg.path_raw_D)

def Separate_Raw_Image_Min() : 
    print("separating  2D and 3D Images")
    MakeDir(cfg.path_raw_A)
    MakeDir(cfg.path_raw_D)
    MakeDir(cfg.path_raw_A+"Cam0\\")
    MakeDir(cfg.path_raw_A+"Cam1\\")
    MakeDir(cfg.path_raw_D+"Cam0\\")
    MakeDir(cfg.path_raw_D+"Cam1\\")
    path_0 = cfg.path_raw+"Cam0\\"
    path_1 = cfg.path_raw+"Cam1\\"
    
    for file in os.listdir(path_0) :
        if file.endswith(".raw") :
            oldPath = path_0 + file
            if "_A_" in file :
                shutil.copy(oldPath , cfg.path_raw_A+"Cam0\\" )
            elif "_D_" in file :
                shutil.copy(oldPath , cfg.path_raw_D+"Cam0\\")
    
    for file in os.listdir(path_1) :
        if file.endswith(".raw") :
            oldPath = path_1 + file
            if "_A_" in file :
                shutil.copy(oldPath , cfg.path_raw_A+"Cam1\\" )
            elif "_D_" in file :
                shutil.copy(oldPath , cfg.path_raw_D+"Cam1\\")
                

def Do_Preprocessing_Entry(preprocessing) :
    
    print("Started Preprocessing")
    MakeDir(cfg.path_PP)
    MakeDir(cfg.path_PP_A)
    MakeDir(cfg.path_PP_D)
    InDepth = np.zeros((cfg.ip_w , cfg.ip_h) ,dtype=np.uint16 )
    InIR = np.zeros((cfg.ip_w , cfg.ip_h) ,dtype=np.uint16 )
    OutDepth = np.zeros((cfg.width , cfg.height) ,dtype=np.uint16 )
    ResizeIR = np.zeros((cfg.width , cfg.height) ,dtype=np.uint16 )
    cnt = 0
    ret = preprocessing.InitializePreProcessing_core(bytes(cfg.path_to_Bin, 'utf-8') , ctypes.c_int(0xFFFFFFFD) )
    #ret = preprocessing.InitializePreProcessing_DAT(bytes(cfg.input_dat_path , 'utf-8') , ctypes.c_int(0xFFFFFFFD)  , ctypes.c_bool(False)  )

    if (ret != 0) :
        sys.exit("ERROR in Initializing : "+cfg.path_to_Bin)

    for hex_Ir in dict_raw_2d :
        for hex_depth in dict_raw_3d :

            if(hex_depth == hex_Ir) : 
          
                ret = preprocessing.LoadRaw(bytes(cfg.path_raw_D+ dict_raw_3d[hex_depth], 'utf-8'),InDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.ip_bf)
                if(ret != 0) :
                    sys.exit("ERROR in Loading : "+dict_raw_3d[hex_depth])
                ret = preprocessing.LoadRaw(bytes(cfg.path_raw_A+ dict_raw_2d[hex_Ir], 'utf-8'),InIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.ip_bf)
                if(ret != 0) :
                    sys.exit("ERROR in Loading : "+dict_raw_2d[hex_Ir])
                path_A = cfg.path_PP_A+"/PP_2D ("+str(hex_Ir+1)+").raw"
                path_D = cfg.path_PP_D+"/PP_3D ("+str(hex_depth+1)+").raw"
                if(cfg.IsVga == 1 ) :
                    ret = preprocessing.Preprocessing_core_PL_VGA(InDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)), OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , InIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , 0 )
                else : 
                    ret = preprocessing.Preprocessing_core_PL(InDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)), OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , InIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , 0)
                if (ret != 0) :
                    sys.exit("ERROR in Processing ")
                ret = preprocessing.SaveRaw(bytes(path_A , 'utf-8') ,ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize )
                if(ret != 0) :
                    sys.exit("ERROR in saving : " + path_A)
                ret = preprocessing.SaveRaw(bytes(path_D , 'utf-8') ,OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)), cfg.buffersize )
                if(ret != 0) :
                    sys.exit("ERROR in saving : " + path_D)
                cnt = cnt+1
                if not hex_depth in  dict_PP_2d :
                    dict_PP_2d[hex_Ir] = "PP_2D ("+str(hex_Ir+1)+").raw"
                else :
                    print("remove at :" + hex_depth)
                if not hex_depth in dict_PP_3d : 
                    dict_PP_3d[hex_depth] = "PP_3D ("+str(hex_Ir+1)+").raw"
                else :
                    print("remove at :" + hex_depth)
                break



    print("pre-processing complete :"+str(cnt)+"images")


def Do_Preprocessing_Min(preprocessing) :
    print("Started Preprocessing")
    MakeDir(cfg.path_PP)
    MakeDir(cfg.path_PP_A)
    MakeDir(cfg.path_PP_A+"Cam0\\")
    MakeDir(cfg.path_PP_A+"Cam1\\")
    MakeDir(cfg.path_PP_D)
    MakeDir(cfg.path_PP_D+"Cam0\\")
    MakeDir(cfg.path_PP_D+"Cam1\\")

    InDepth = np.zeros((cfg.ip_w , cfg.ip_h) ,dtype=np.uint16 )
    InIR = np.zeros((cfg.ip_w , cfg.ip_h) ,dtype=np.uint16 )
    OutDepth = np.zeros((cfg.width , cfg.height) ,dtype=np.uint16 )
    ResizeIR = np.zeros((cfg.width , cfg.height) ,dtype=np.uint16 )
    
    path_D_0 = cfg.path_raw_D + "cam0\\"
    path_D_1 = cfg.path_raw_D + "cam1\\"
    path_A_0 = cfg.path_raw_A + "cam0\\"
    path_A_1 = cfg.path_raw_A + "cam1\\"
 
    cnt0 = 0
    ret = preprocessing.InitializePreProcessing_core_High(bytes(cfg.path_to_Bin, 'utf-8') , ctypes.c_int(2) , ctypes.c_int(0x05010001) )
    if (ret != 0) :
        print("ERROR in Initializing : "+cfg.path_to_Bin)
#cam0
    preprocessing.setFlipMode(ctypes.c_int32(0) )

    cnt0 = 0
    for hex_Ir in dict_raw_2d :
        for hex_depth in dict_raw_3d :

            if(hex_depth == hex_Ir) : 
          
                ret = preprocessing.LoadRaw(bytes(path_D_0 + dict_raw_3d[hex_depth], 'utf-8'),InDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.ip_bf)
                if(ret != 0) :
                    sys.exit("ERROR in Loading : "+dict_raw_3d[hex_depth])
                ret = preprocessing.LoadRaw(bytes(path_A_0+ dict_raw_2d[hex_Ir], 'utf-8'),InIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.ip_bf)
                if(ret != 0) :
                    sys.exit("ERROR in Loading : "+dict_raw_2d[hex_Ir])
                path_A = cfg.path_PP_A +"/Cam0/PP_2D ("+str(hex_Ir+1)+").raw"
                path_D = cfg.path_PP_D +"/Cam0/PP_3D ("+str(hex_depth+1)+").raw"
                if(cfg.IsVga == 1 ) :
                    ret = preprocessing.Preprocessing_core_PL_VGA(InDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)), OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , InIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , 0 )
                else : 
                    ret = preprocessing.Preprocessing_core_PL(InDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)), OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , InIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , 0)
                if (ret != 0) :
                    sys.exit("ERROR in Processing ")
                ret = preprocessing.SaveRaw(bytes(path_A , 'utf-8') ,ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize )
                if(ret != 0) :
                    sys.exit("ERROR in saving : " + path_A)
                ret = preprocessing.SaveRaw(bytes(path_D , 'utf-8') ,OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)), cfg.buffersize )
                if(ret != 0) :
                    sys.exit("ERROR in saving : " + path_D)
                cnt0 = cnt0+1
                if not hex_depth in  dict_PP_2d :
                    dict_PP_2d[hex_Ir] = "PP_2D ("+str(hex_Ir+1)+").raw"
                else :
                    print("remove at :" + hex_depth)
                if not hex_depth in dict_PP_3d : 
                    dict_PP_3d[hex_depth] = "PP_3D ("+str(hex_Ir+1)+").raw"
                else :
                    print("remove at :" + hex_depth)
                break
    
#cam 1
    preprocessing.setFlipMode(ctypes.c_int32(4) )
    cnt1 = 0
    for hex_Ir in dict_raw_2d_1 :
        for hex_depth in dict_raw_3d_1 :

            if(hex_depth == hex_Ir) : 
          
                ret = preprocessing.LoadRaw(bytes(path_D_1 + dict_raw_3d_1[hex_depth], 'utf-8'),InDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.ip_bf)
                if(ret != 0) :
                    sys.exit("ERROR in Loading : "+dict_raw_3d_1[hex_depth])
                ret = preprocessing.LoadRaw(bytes(path_A_1+ dict_raw_2d_1[hex_Ir], 'utf-8'),InIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.ip_bf)
                if(ret != 0) :
                    sys.exit("ERROR in Loading : "+dict_raw_2d_1[hex_Ir])
                path_A = cfg.path_PP_A +"/Cam1/PP1_2D ("+str(hex_Ir+1)+").raw"
                path_D = cfg.path_PP_D +"/Cam1/PP1_3D ("+str(hex_depth+1)+").raw"
                if(cfg.IsVga == 1 ) :
                    ret = preprocessing.Preprocessing_core_PL_VGA(InDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)), OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , InIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , 0 )
                else : 
                    ret = preprocessing.Preprocessing_core_PL(InDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)), OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , InIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , 0)
                if (ret != 0) :
                    sys.exit("ERROR in Processing ")
                ret = preprocessing.SaveRaw(bytes(path_A , 'utf-8') ,ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize )
                if(ret != 0) :
                    sys.exit("ERROR in saving : " + path_A)
                ret = preprocessing.SaveRaw(bytes(path_D , 'utf-8') ,OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)), cfg.buffersize )
                if(ret != 0) :
                    sys.exit("ERROR in saving : " + path_D)
                cnt1 = cnt1+1
                if not hex_depth in  dict_PP_2d_1 :
                    dict_PP_2d_1[hex_Ir] = "PP1_2D ("+str(hex_Ir+1)+").raw"
                else :
                    print("remove at :" + hex_depth)
                if not hex_depth in dict_PP_3d_1 : 
                    dict_PP_3d_1[hex_depth] = "PP1_3D ("+str(hex_Ir+1)+").raw"
                else :
                    print("remove at :" + hex_depth)
                break

    print("pre-processing complete :"+str(cnt0)+"cam0 images")
    print("pre-processing complete :"+str(cnt1)+"cam1 images")




def checkArguments(args) :
    
    if (args.f.lower() == 'qvga') :
        cfg.IsVga = 0
    elif (args.f.lower() == 'vga' ) :
        cfg.IsVga = 1
    else :
         raise argparse.ArgumentTypeError("Invalid option for -f "+str(args.f))

    if (args.sv.lower() == 'yes') :
        cfg.keep_op = 1
    elif (args.sv.lower() == 'no' ) :
        cfg.keep_op = 0
    else :
         raise argparse.ArgumentTypeError("Invalid option for -sv "+str(args.sv))
    if (args.ov.lower() == 'entry') :
        cfg.version = 1
    elif (args.ov.lower() == 'min' ) :
        cfg.version = 2
        cfg.PreprocessingDLL = "OfflineFilterSDK.dll"
    elif (args.ov.lower() == 'max' ) :
        cfg.version = 3
    else :
         raise argparse.ArgumentTypeError("Invalid version type "+str(args.ov))
    
    input_dat = Path(args.i).resolve()
    if input_dat.exists() and args.i.endswith('.dat') :
        cfg.input_dat_path = args.i
    else :
         raise argparse.ArgumentTypeError("Invalid path to .dat file "+str(args.i))

    if  args.ov.lower() == 'entry' :
        input_ref = Path(args.ref).resolve()
        if input_ref.exists() and args.ref.endswith('.csv') :
            cfg.ref_file = args.ref
        else :
             raise argparse.ArgumentTypeError("Invalid path to ref file "+str(args.ref))
    
    input_dat = Path(args.p2).resolve()
    if input_dat.exists() :
        cfg.path_test_2D = args.p2
        if not args.p2.endswith('\\') :
            cfg.path_test_2D = cfg.path_test_2D + '\\'
    else :
         raise argparse.ArgumentTypeError("Invalid path to 2D PP images : "+str(args.p2))
    
    input_dat = Path(args.p3).resolve()
    if input_dat.exists() :
        cfg.path_test_3D = args.p3
        if not args.p3.endswith('\\') :
            cfg.path_test_3D = cfg.path_test_3D + '\\'
    else :
         raise argparse.ArgumentTypeError("Invalid path to 3D PP images : "+str(args.p3)) 
    
    output_path = Path(args.o).resolve()
    if output_path.exists() :
        cfg.Unprocessed_raw_Images = args.o
    else :
         raise argparse.ArgumentTypeError("Invalid path to output  file"+str(args.o))
    

def custom_usage() : 
    return '''
    
    usage 1 : SQT_Automation_main.py -h 
    usage 2 : SQT_Automation_main.py -i I -p2 P2 -p3 P3 -ref ref [-ov OV] [-sv SV] [-f F] [-o O]
    '''
def getXYZvalues() : 
    with open(cfg.ref_file , mode='r') as csv_file:
        csv_reader = csv.DictReader(csv_file , delimiter = ',')
        for row in csv_reader:
            xyzdata[int(row["Frame Count: "])]  =    {             
                'ITGC_D_Hand1_PosU' : int(row["ITGC_D_Hand1_PosU: "]),       #1
                'ITGC_D_Hand1_PosV' : int(row["ITGC_D_Hand1_PosV : "]) ,     #2
                'ITGC_D_Hand1_PosX' : int(row["ITGC_D_Hand1_PosX: "] ),      #3
                'ITGC_D_Hand1_PosY' : int(row["ITGC_D_Hand1_PosY : "] ),     #4
                'ITGC_D_Hand1_PosZ' : int(row["ITGC_D_Hand1_PosZ"] ) ,  

                'ITGC_D_Hand1_PosU_FT' : int(row["ITGC_D_Hand1_PosU_FT: "]),       #1
                'ITGC_D_Hand1_PosV_FT' : int(row["ITGC_D_Hand1_PosV_FT : "]) ,     #2
                'ITGC_D_Hand1_PosX_FT' : int(row["ITGC_D_Hand1_PosX_FT: "] ),      #3
                'ITGC_D_Hand1_PosY_FT' : int(row["ITGC_D_Hand1_PosY_FT : "] ),     #4
                'ITGC_D_Hand1_PosZ_FT' : int(row["ITGC_D_Hand1_PosZ_FT"] ),         #      #

                'ITGC_D_Hand2_PosU' : int(row["ITGC_D_Hand2_PosU: "]),       #1
                'ITGC_D_Hand2_PosV' : int(row["ITGC_D_Hand2_PosV : "]) ,     #2
                'ITGC_D_Hand2_PosX' : int(row["ITGC_D_Hand2_PosX: "] ),      #3
                'ITGC_D_Hand2_PosY' : int(row["ITGC_D_Hand2_PosY : "] ),     #4
                'ITGC_D_Hand2_PosZ' : int(row["ITGC_D_Hand2_PosZ"] ) ,        #
                
                'ITGC_D_Hand2_PosU_FT' : int(row["ITGC_D_Hand2_PosU_FT: "]),       #1
                'ITGC_D_Hand2_PosV_FT' : int(row["ITGC_D_Hand2_PosV_FT : "]) ,     #2
                'ITGC_D_Hand2_PosX_FT' : int(row["ITGC_D_Hand2_PosX_FT: "] ),      #3
                'ITGC_D_Hand2_PosY_FT' : int(row["ITGC_D_Hand2_PosY_FT : "] ),     #4
                'ITGC_D_Hand2_PosZ_FT' : int(row["ITGC_D_Hand2_PosZ_FT"] ) ,
                
                'ITGC_D_Hand1_PosU' : int(row["ITGC_D_Hand1_PosU: "]),       #1
                'ITGC_D_Hand1_PosV' : int(row["ITGC_D_Hand1_PosV : "]) ,     #2
                'ITGC_D_Hand1_PosX' : int(row["ITGC_D_Hand1_PosX: "] ),      #3
                'ITGC_D_Hand1_PosY' : int(row["ITGC_D_Hand1_PosY : "] ),     #4
                'ITGC_D_Hand1_PosZ' : int(row["ITGC_D_Hand1_PosZ"] ) ,
                
                'ITGC_P_Hand1_PosU' : int(row["ITGC_P_Hand1_PosU: "]),       #1
                'ITGC_P_Hand1_PosV' : int(row["ITGC_P_Hand1_PosV : "]) ,     #2
                'ITGC_P_Hand1_PosX' : int(row["ITGC_P_Hand1_PosX: "] ),      #3
                'ITGC_P_Hand1_PosY' : int(row["ITGC_P_Hand1_PosY : "] ),     #4
                'ITGC_P_Hand1_PosZ' : int(row["ITGC_P_Hand1_PosZ"] )  ,       #

                'ITGC_P_Hand1_PosU_FT' : int(row["ITGC_P_Hand1_PosU_FT: "]),       #1
                'ITGC_P_Hand1_PosV_FT' : int(row["ITGC_P_Hand1_PosV_FT : "]) ,     #2
                'ITGC_P_Hand1_PosX_FT' : int(row["ITGC_P_Hand1_PosX_FT: "] ),      #3
                'ITGC_P_Hand1_PosY_FT' : int(row["ITGC_P_Hand1_PosY_FT : "] ),     #4
                'ITGC_P_Hand1_PosZ_FT' : int(row["ITGC_P_Hand1_PosZ_FT"] ) ,        #

                'ITGC_P_Hand2_PosU' : int(row["ITGC_P_Hand2_PosU: "]),       #1
                'ITGC_P_Hand2_PosV' : int(row["ITGC_P_Hand2_PosV : "]) ,     #2
                'ITGC_P_Hand2_PosX' : int(row["ITGC_P_Hand2_PosX: "] ),      #3
                'ITGC_P_Hand2_PosY' : int(row["ITGC_P_Hand2_PosY : "] ),     #4
                'ITGC_P_Hand2_PosZ' : int(row["ITGC_P_Hand2_PosZ"] )  ,       #

                'ITGC_P_Hand2_PosU_FT' : int(row["ITGC_P_Hand2_PosU_FT: "]),       #1
                'ITGC_P_Hand2_PosV_FT' : int(row["ITGC_P_Hand2_PosV_FT : "]) ,     #2
                'ITGC_P_Hand2_PosX_FT' : int(row["ITGC_P_Hand2_PosX_FT: "] ),      #3
                'ITGC_P_Hand2_PosY_FT' : int(row["ITGC_P_Hand2_PosY_FT : "] ),     #4
                'ITGC_P_Hand2_PosZ_FT' : int(row["ITGC_P_Hand2_PosZ_FT"] )         #
                }

            
def calculateXYZ(preprocessing , xlReport , filenames)  :
    
    OutDepth = np.zeros((cfg.width , cfg.height) ,dtype=np.uint16 )
    ResizeIR = np.zeros((cfg.width , cfg.height) ,dtype=np.uint16 )
    InDepth = np.zeros((cfg.ip_w , cfg.ip_h) ,dtype=np.uint16 )
    InIR = np.zeros((cfg.ip_w , cfg.ip_h) ,dtype=np.uint16 )

    hand = ["Hand1" , "Hand2" ]
    person = ["D", "P" ]
    ft = ["" , "_FT"]   
    
    
    
    Report_path = Path(cfg.Report_path).resolve()
    if not Report_path.exists() : 
        os.mkdir(cfg.Report_path)
    
    xlReport.set_workbook_path(cfg.Report_path+cfg.Report_CSV_Compare)
    localtime = time.asctime( time.localtime(time.time()) )
    xlReport.init_workbook(localtime)
    #print(filenames)
    ret = preprocessing.GetRTMatrix(bytes(filenames[0] , 'utf-8'))
    if (ret is not  0) : 
        sys.exit("Error genrating RT matrix")
    
    cur_RT = 0 
    cur_mul = 255
    
    for data in xyzdata :

        image2D = dict_PP_2d[data]
        image3D = dict_PP_3d[data]
        image2D = cfg.path_PP_A + image2D
        image3D = cfg.path_PP_D + image3D
        #print(data)
        if(data > cur_mul) :
            cur_mul = cur_mul + 255 
            if (cur_RT+1 ) < len(filenames) :
                cur_RT = cur_RT + 1
                ret = preprocessing.GetRTMatrix(bytes(filenames[cur_RT] , 'utf-8' ))
                #print("changed RT ")
                if (ret is not  0) : 
                    sys.exit("Error genrating RT matrix")


        ret = preprocessing.LoadRaw(bytes(image2D, 'utf-8'),ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize )
        if(ret != 0) :
           sys.exit("ERROR in Loading : "+image2D)
        ret = preprocessing.LoadRaw(bytes(image3D, 'utf-8'),OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
        if(ret != 0) :
            sys.exit("ERROR in Loading : "+ image3D)
        
  
        
        
        pat = re.search(r"(\d{4}_\d{2}_\d{2}_\d{2}_\d{2}_\d{2}_\d{10})",dict_raw_2d[data] )

        for p in person :
            for h in hand :
               for f in ft : 
                
                    type = 'ITGC_'+p+'_'+h+f
                    u = 'ITGC_'+p+'_'+h+'_PosU'+f
                    v = 'ITGC_'+p+'_'+h+'_PosV'+f
                    x1 = 'ITGC_'+p+'_'+h+'_PosX'+f
                    y1 = 'ITGC_'+p+'_'+h+'_PosY'+f
                    z1 = 'ITGC_'+p+'_'+h+'_PosZ'+f
                
                    data_xyz = {
    
                    'patch_y' : ctypes.c_uint16(xyzdata[data][v]),
                    'patch_x'  : ctypes.c_uint16(xyzdata[data][u]),
                    'patch_h' : ctypes.c_uint16(1),
                    'patch_w' : ctypes.c_uint16(1),
                
                    'width' : ctypes.c_int32(cfg.width),
                    'height' : ctypes.c_int32(cfg.height),
                    'usmin'  : ctypes.c_uint16(100),
                    'usmax' : ctypes.c_uint16(4000),
                    'x' : ctypes.c_float(0.00),
                    'y' : ctypes.c_float(0.00),
                    'z' : ctypes.c_float(0.00),
                    'camera' :  ctypes.c_int(0)
                    }
           
                    if (xyzdata[data][v] is 0 or  xyzdata[data][u] is  0 or xyzdata[data][u] >= cfg.width or xyzdata[data][v] >= cfg.height   ) :
    
                        Information_csv = {
                            'type' :  type,
                            'image' : dict_PP_2d[data] ,
                            'Frame Count' : data ,
                            'Time' : pat.group(1) ,
                            'u' : xyzdata[data][u] ,
                            'v' : xyzdata[data][v] ,
                            'ex' : xyzdata[data][x1] ,
                            'ey' : xyzdata[data][y1] ,
                            'ez' : xyzdata[data][z1] ,
                            'ax' : -32768 ,
                            'ay' : -32768,
                            'az' : -32768 
    
                        } 
                    else :
                
                        ret = preprocessing.getXYZ(  OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)), 
                        ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , data_xyz  )
                        if ( data_xyz['x'].value == 0  and data_xyz['y'].value == 0  and data_xyz['z'].value == 0 ) :
                            Information_csv = {
                            'type' :  type,
                            'image' : dict_PP_2d[data] ,
                            'Frame Count' : data ,
                            'Time' : pat.group(1) ,
                            'u' : xyzdata[data][u] ,
                            'v' : xyzdata[data][v] ,
                            'ex' : xyzdata[data][x1] ,
                            'ey' : xyzdata[data][y1] ,
                            'ez' : xyzdata[data][z1] ,
                            'ax' : -32768 ,
                            'ay' : -32768,
                            'az' : -32768
    
                            } 
                        else :
                            Information_csv = {
                            'type' :  type,
                            'image' : dict_PP_2d[data] ,
                            'Frame Count' : data ,
                            'Time' : pat.group(1) ,
                            'u' : xyzdata[data][u] ,
                            'v' : xyzdata[data][v] ,
                            'ex' : xyzdata[data][x1] ,
                            'ey' : xyzdata[data][y1] ,
                            'ez' : xyzdata[data][z1] ,
                            'ax' : data_xyz['x'].value ,
                            'ay' : data_xyz['y'].value,
                            'az' : data_xyz['z'].value 
    
                            } 
    
                    xlReport.add_data(Information_csv)


    
    
                    
    xlReport.close()



def getCalibFiles() :
    filenames = glob.glob(cfg.path_to_calib)
    print("get calib files : ")
    print(filenames)
    if(filenames == []) :
        sys.exit("No callibration files found in provided path : "+ cfg.path_to_calib )
    return filenames



def main() :
        
#parse arguments
    
    parser = argparse.ArgumentParser(description="SQT automation Tool" , add_help=False , usage = custom_usage() )
    parser.add_argument('-h'  , action='store_true',  help = "show this help message and exit" , default = False)
    parser.add_argument("-i",help = 'Path of input .dat file(name of .dat is mandatory).')
    parser.add_argument("-ref",help = 'Path of input refrance file (name of ref file is mandatory).' )
    parser.add_argument("-p2", help = 'Path of preprocessed 2D images from SQT' , )
    parser.add_argument("-p3" , help = 'Path of preprocessed 3D images from SQT')
    parser.add_argument("-ov" , help = 'Provide "entry" , "min" or "max" for OMS Version',default = "entry")
    parser.add_argument("-sv" , help = 'Provide "yes" or "no" to save intermediate raw and PP images(by default - yes)',default = "yes")
    parser.add_argument("-f" , help = 'Provide formate of the preprocessed images(i.e. "VGA" or "QVGA")',default = "QVGA")
    parser.add_argument("-o" , help = 'Provide Output directory path (by default - /output)',default = "output")

    args=parser.parse_args()
    if args.h  is True or not len(sys.argv) > 1:
        parser.print_help()
        sys.exit()

    if args.i is None :
        raise argparse.ArgumentTypeError("to few arguments : please provide path to input dat file")
    elif args.p2 is None :
        raise argparse.ArgumentTypeError("to few arguments : please provide path to input 2D preprocessed images")
    elif args.p3 is None :
        raise argparse.ArgumentTypeError("to few arguments : please provide path to input 3D preprocessed images")
    elif args.ref is None and args.ov == "Entry" :
         raise argparse.ArgumentTypeError("to few arguments : please provide path to input ref file")
    else :
        checkArguments(args)


#start process flow
    
    Extract_Images()
    preprocessing = OfflineFilterSDK.preprocessing(cfg.PreprocessingDLL , cfg.version)
    if (cfg.version == 1) : 
        xlReport = CSV_ReportGenerator.ReportGenerator(  cfg.path_to_calib , getuser() , args.ov )
        Separate_Raw_Image_Entry()
        getFrameCount(preprocessing)
        Do_Preprocessing_Entry(preprocessing)
        Compare_Images_FC_Entry(preprocessing)
        filenames = getCalibFiles()
        getXYZvalues()
        calculateXYZ(preprocessing , xlReport , filenames)

    elif (cfg.version == 2)   :
        Separate_Raw_Image_Min ()
        getFrameCount(preprocessing)
        Do_Preprocessing_Min(preprocessing)
        Compare_Images_FC_Min(preprocessing)
        print("Phase - 2 is yet to define for min")
    else :
        print("Yet to Define for max ") 


if __name__ == '__main__':
	main()

