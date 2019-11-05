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
#created classes
from Include import ImageExtractor
from Include import OfflineFilterSDK
from Include import ImageCompare
from Config import config as cfg
from Include import ReportGenerator
import argparse


def Manage_Intermediate_output() : 
    if (cfg.keep_op == 0) : 
        output_dir = Path(cfg.Unprocessed_raw_Images).resolve()
        if output_dir.exists() :
            shutil.rmtree(cfg.Unprocessed_raw_Images)
            print("Removing intermidiate raw and PP images")
    else :
        print("Intermediate raw and PP images has been made available at :"+str(cfg.Unprocessed_raw_Images))


def set_env() :
    output_dir = Path(cfg.Unprocessed_raw_Images).resolve()
    if output_dir.exists() :
        shutil.make_archive(cfg.path_old, "zip", cfg.Unprocessed_raw_Images )
        shutil.rmtree(cfg.Unprocessed_raw_Images)

def MakeDir(path_) :
    output_dir = Path(path_).resolve()
    if output_dir.exists() :
        shutil.rmtree(path_)
    os.mkdir(path_)

def Compare_Images_FC(preprocessing , version) :
    

#init xls report
    Report_path = Path(cfg.Report_path).resolve()
    if not Report_path.exists() : 
        os.mkdir(cfg.Report_path)
    xlReport = ReportGenerator.ReportGenerator()
    xlReport.set_workbook_path(cfg.Report_path+cfg.Report_Image_Compare)
    xlReport.create_worksheet()
    xlReport.set_header()

    image11 = np.zeros((cfg.width , cfg.height) ,dtype=np.uint16 )
    image21 = np.zeros((cfg.width , cfg.height) ,dtype=np.uint16 )
    ImgComp = ImageCompare.ImageCompare()
 
 
#list with duplicates 
#2D    
    image_test_2d = []
    hex_test_2d = []
    image_PP_2d = []
    hex_PP_2d = []
#3D        
    image_test_3d = []
    hex_test_3d = []
    image_PP_3d = []
    hex_PP_3d = []
 
#lists with non - duplicates 
#2D    
    hex_test_2d_nd = []
    image_test_2d_nd = []
    hex_PP_2d_nd = []
    image_PP_2d_nd = []
    
#3D
    hex_test_3d_nd = []
    image_test_3d_nd = []
    hex_PP_3d_nd = []
    image_PP_3d_nd = []

#get hex values 2D   
    
    for image1 in os.listdir(cfg.path_test_2D) :
        path1 = cfg.path_test_2D + image1
        ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
        image_test_2d.append(image1)
        hex_test_2d.append(hex(image11[0][1]))

    for image1 in os.listdir(cfg.path_PP_A) :
        path1 = cfg.path_PP_A + image1
        ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
        image_PP_2d.append(image1)
        hex_PP_2d.append(hex(image11[0][1]))


    for hex1 in hex_test_2d :
        f = 0
        for hex2 in hex_test_2d_nd :
            if (hex1 == hex2) : 
                f =1
                print("removing as duplicate frame count as(2D_test): "+str(hex2))
                break
        if (f == 0):
            hex_test_2d_nd.append(hex1)
            image_test_2d_nd.append(image_test_2d[hex_test_2d.index(hex1)])

#remove duplicate hex 2D
            
    for hex1 in hex_PP_2d:
        f = 0
        for hex2 in hex_PP_2d_nd :
            if (hex1 == hex2) : 
                f =1
                print("removing as duplicate frame count(2D_PP): "+str(hex2) )
                break
        if (f == 0):
            hex_PP_2d_nd.append(hex1)
            image_PP_2d_nd.append(image_PP_2d[hex_PP_2d.index(hex1)])

# compare Images 2D 

    for hex_test in hex_test_2d_nd :
        f = 0
        for hex_PP in hex_PP_2d_nd : 
            if (hex_test == hex_PP) :
                index_test = hex_test_2d_nd.index(hex_test)
                index_pp = hex_PP_2d_nd.index(hex_PP)
                path1 = cfg.path_test_2D + image_test_2d_nd[index_test]
                path2 = cfg.path_PP_A + image_PP_2d_nd[index_pp]
                ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
                if not ( ret == 0 ):
                    sys.exit("Error in loading test images(2D) ! please check OMS Version (use -ov to provide  correct OMS version )"+ version)
                ret = preprocessing.LoadRaw(bytes(path2, 'utf-8'),image21.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
                if not ( ret == 0 ):
                    sys.exit("Error in loading PP images(2D) ! please check OMS Version (use -ov to provide  correct OMS version )"+ version)
                ret = preprocessing.LoadRaw(bytes(path2, 'utf-8'),image21.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
                ret = preprocessing.LoadRaw(bytes(path2, 'utf-8'),image21.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
                ret = ImgComp.Get_Error(image11 , image21)
                pat = re.search(r"(\d{4}_\d{2}_\d{2}_\d{2}_\d{2}_\d{2}_\d{10})",image_PP_2d_nd[index_pp])
                xlReport.add_data("2D" , image_test_2d_nd[index_test] , image_PP_2d_nd[index_pp] , pat.group(1) ,  hex_test , math.sqrt(ret)*100 )
                f = 1
                break
        if(f == 0) :
            index_test = hex_test_2d_nd.index(hex_test)
            xlReport.add_data("2D" , image_test_2d_nd[index_test] , "N/A" , "N/A" ,  hex_test , "frame NOT Found" )
            
#get hex values   3D 
    
    for image1 in os.listdir(cfg.path_test_3D) :
        path1 = cfg.path_test_3D + image1
        ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
        image_test_3d.append(image1)
        hex_test_3d.append(hex(image11[0][1]))

    for image1 in os.listdir(cfg.path_PP_D) :
        path1 = cfg.path_PP_D + image1
        ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
        image_PP_3d.append(image1)
        hex_PP_3d.append(hex(image11[0][1]))
        
    for hex1 in hex_test_3d :
        f = 0
        for hex2 in hex_test_3d_nd :
            if (hex1 == hex2) : 
                f =1
                print("removing as duplicate frame count as(3D_test): "+str(hex2))
                break
        if (f == 0):
            hex_test_3d_nd.append(hex1)
            image_test_3d_nd.append(image_test_3d[hex_test_3d.index(hex1)])

#remove duplicate hex 3D
            
    for hex1 in hex_PP_3d:
        f = 0
        for hex2 in hex_PP_3d_nd :
            if (hex1 == hex2) : 
                f =1
                print("removing as duplicate frame count(3D_PP): "+str(hex2) )
                break
        if (f == 0):
            hex_PP_3d_nd.append(hex1)
            image_PP_3d_nd.append(image_PP_3d[hex_PP_3d.index(hex1)])

# compare Images 3D 

    for hex_test in hex_test_3d_nd :
        f = 0
        for hex_PP in hex_PP_3d_nd : 
            if (hex_test == hex_PP) :
                index_test = hex_test_3d_nd.index(hex_test)
                index_pp = hex_PP_3d_nd.index(hex_PP)
                path1 = cfg.path_test_3D + image_test_3d_nd[index_test]
                path2 = cfg.path_PP_D + image_PP_3d_nd[index_pp]
                ret = preprocessing.LoadRaw(bytes(path1, 'utf-8'),image11.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
                if not ( ret == 0 ):
                   sys.exit("Error in loading test images(3D) ! please check OMS Version (use -ov to provide  correct OMS version )"+ version)
                ret = preprocessing.LoadRaw(bytes(path2, 'utf-8'),image21.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
                if not ( ret == 0 ):
                    sys.exit("Error in loading PP images(3D) ! please check OMS Version (use -ov to provide  correct OMS version )"+ version)
                ret = preprocessing.LoadRaw(bytes(path2, 'utf-8'),image21.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize)
                ret = ImgComp.Get_Error(image11 , image21)
                pat = re.search(r"(\d{4}_\d{2}_\d{2}_\d{2}_\d{2}_\d{2}_\d{10})",image_PP_3d_nd[index_pp])
                xlReport.add_data("3D" , image_test_3d_nd[index_test] , image_PP_3d_nd[index_pp] , pat.group(1) ,  hex_test , ret*100 )
                f = 1
                break
        if(f == 0) :
            index_test = hex_test_3d_nd.index(hex_test)
            xlReport.add_data("3D" , image_test_3d_nd[index_test] , " N/A" , "N/A" ,  hex_test , "frame NOT Found" )
    
    xlReport.close()
 

def Extract_Images() : 
    print("Extracting Images")
    MakeDir(cfg.Unprocessed_raw_Images)
    imgExt = ImageExtractor.ImageExtractor(cfg.input_dat_path ,cfg.image_extractor_path , cfg.Unprocessed_raw_Images )
    ret = imgExt.Resolve()
    if (ret == 1) :
        sys.exit('Please set correct path of input DAT file(' + str(cfg.input_dat_path) + ')')
    elif (ret == 2) : 
        sys.exit('Please set correct path of ImageExtractor(' + str(cfg.image_extractor_path) + ')')
    elif (ret == 3) :
        sys.exit('Please set correct path of output directory(' + str(cfg.Unprocessed_raw_Images) + ')')
    else :
        imgExt.Extract_Dat_info()
        ret = imgExt.Run()
        if ret.returncode == 0:
            print('Image extractor : Success')
        else : 
            sys.exit('Image extractor : Fail') 
            
           
def Saprate_Raw_Image() : 
    print("Saprating 2d and 3D Images")
    MakeDir(cfg.path_raw_A)
    MakeDir(cfg.path_raw_D)
    for file in os.listdir(cfg.path_raw) :
        if file.endswith(".raw") :
            oldPath = cfg.path_raw + file
            if "_A_" in file :
                shutil.copy(oldPath , cfg.path_raw_A )
            elif "_D_" in file :
                shutil.copy(oldPath , cfg.path_raw_D)
                
def Do_Preprocessing(preprocessing) :
    print("Started Preprocessing")
    MakeDir(cfg.path_PP)
    MakeDir(cfg.path_PP_A)
    MakeDir(cfg.path_PP_D)
    InDepth = np.zeros((cfg.ip_w , cfg.ip_h) ,dtype=np.uint16 )
    InIR = np.zeros((cfg.ip_w , cfg.ip_h) ,dtype=np.uint16 )
    OutDepth = np.zeros((cfg.width , cfg.height) ,dtype=np.uint16 )
    ResizeIR = np.zeros((cfg.width , cfg.height) ,dtype=np.uint16 )
    cnt = 0
    ret = preprocessing.InitializePreProcessing_core(bytes(cfg.path_to_Bin, 'utf-8'))
    if (ret != 0) :
        print("ERROR in Initializing"+cfg.path_to_Bin)
    else :
        i = 1
        for Image_D in sorted(os.listdir(cfg.path_raw_D)) :
            for date in  re.findall(r"\d{4}_\d{2}_\d{2}_\d{2}_\d{2}_\d{2}_\d{10}", Image_D) :
                for Image_A in sorted(os.listdir(cfg.path_raw_A))  :
                    for date in re.findall(date , Image_A) :
                        ret = preprocessing.LoadRaw(bytes(cfg.path_raw_D+Image_D, 'utf-8'),InDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.ip_bf)
                        ret = preprocessing.LoadRaw(bytes(cfg.path_raw_A+Image_A, 'utf-8'),InIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.ip_bf)
                        print(InDepth)
                        path_A = cfg.path_PP_A+"/PP_("+str(i)+")"+Image_A
                        path_D = cfg.path_PP_D+"/PP_("+str(i)+")"+Image_D
                        i = i+1
                        if(ret == 0) :
                            if(cfg.IsVga == 1 ) :
                                ret = preprocessing.Preprocessing_core_PL_VGA(InDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)), OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , InIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , 0 )
                            else : 
                                ret = preprocessing.Preprocessing_core_PL(InDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)), OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , InIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , 0)
                            print(OutDepth)
                            if (ret == 0) : 
                                ret = preprocessing.SaveRaw(bytes(path_A , 'utf-8') ,ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , cfg.buffersize )
                                ret = preprocessing.SaveRaw(bytes(path_D , 'utf-8') ,OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)), cfg.buffersize )
                                cnt = cnt+1
                                if(ret != 0) :
                                    sys.exit("ERROR in saving"+date)
                            else :
                                sys.exit("ERROR in Processing"+date)
                        else :
                            sys.exit("ERROR in Loading"+date)
            
        print("pre-processing complete :"+str(cnt)+"images")

def checkArguments(args) :
    
    if (args.f.lower() == 'qvga') :
        cfg.IsVga = 0
    elif (args.sv.lower() == 'vga' ) :
        cfg.IsVga = 1
    else :
         raise argparse.ArgumentTypeError("Invalid option for -sv "+str(args.sv))
         
    if (args.sv.lower() == 'yes') :
        cfg.keep_op = 1
    elif (args.sv.lower() == 'no' ) :
        cfg.keep_op = 0
    else :
         raise argparse.ArgumentTypeError("Invalid option for -sv "+str(args.sv))
    if (args.ov.lower() == 'high') :
        cfg.version = 1
    elif (args.ov.lower() == 'entry' ) :
        cfg.version = 0
    else :
         raise argparse.ArgumentTypeError("Invalid version type "+str(args.ov))
    
    input_dat = Path(args.Input_Dat_file).resolve()
    if input_dat.exists() and args.Input_Dat_file.endswith('.dat') :
        cfg.input_dat_path = args.Input_Dat_file
    else :
         raise argparse.ArgumentTypeError("Invalid path to .dat file"+str(args.Input_Dat_file))
    
    input_dat = Path(args.Input_PP_files_2D).resolve()
    if input_dat.exists() :
        cfg.path_test_2D = args.Input_PP_files_2D
        if not args.Input_PP_files_2D.endswith('\\') :
            cfg.path_test_2D = cfg.path_test_2D + '\\'
    else :
         raise argparse.ArgumentTypeError("Invalid path to 2D PP images : "+str(args.Input_PP_files_2D))
    
    input_dat = Path(args.Input_PP_files_3D).resolve()
    if input_dat.exists() :
        cfg.path_test_3D = args.Input_PP_files_3D
        if not args.Input_PP_files_3D.endswith('\\') :
            cfg.path_test_3D = cfg.path_test_3D + '\\'
    else :
         raise argparse.ArgumentTypeError("Invalid path to 3D PP images : "+str(args.Input_PP_files_3D))    
    
def main() :
        
#parse arguments
        parser = argparse.ArgumentParser(description="SQT automation Tool")
        parser.add_argument("Input_Dat_file",help = 'Path of input .dat file(name of .dat is mandatory).')
        parser.add_argument("Input_PP_files_2D", help = 'Path of preprocessed 2D images from SQT')
        parser.add_argument("Input_PP_files_3D" , help = 'Path of preprocessed 3D images from SQT')
        parser.add_argument("-ov" , help = 'Provide "entry" or "high" for OMS Version(by default - High)',default = "high")
        parser.add_argument("-sv" , help = 'Provide "yes" or "no" to save intermediate raw and PP images(by default - No)',default = "no")
        parser.add_argument("-f" , help = 'Provide formate of the preprocessed images(i.e. "VGA" or "QVGA")',default = "QVGA")
        
        args=parser.parse_args("")
        
        checkArguments(args)
        start = time.time()

#start process flow
        Extract_Images()
        Saprate_Raw_Image()
        preprocessing = OfflineFilterSDK.preprocessing(cfg.PreprocessingDLL)
        Do_Preprocessing(preprocessing)
        Compare_Images_FC(preprocessing , args.ov)
        Manage_Intermediate_output()
        end = time.time()
        print("Overall Time (in seconds) : "+str(end-start))
        
        '''
        except Exception as e:
        print("Error occurred! "+ str(e))       
        '''
if __name__ == '__main__':
	main()


