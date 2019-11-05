

#Input Path for DAT
input_dat_path = ""

#Image Comparator test data (from Actual SQT process)
path_test_2D = ""
path_test_3D = ""


TOLERANCE_DIFF_PIXELS  = 32
TOLERANCE_PIXEL_WISE_DIFF = 1.0



#set env
image_extractor_path = "ImageExtractor\\ImageExtractor.exe"
Unprocessed_raw_Images = "Output" 
PreprocessingDLL = "OfflineFilterSDK_0.50_release.dll"
path_to_Bin = "\\0000000000\\"

# Raw Images
path_raw =  "\\0000000000\\"
path_raw_A ="\\0000000000\\IR\\"
path_raw_D ="\\0000000000\\Depth\\"

#preprocessed Images
path_PP =  "\\PP\\ "
path_PP_A = "\\PP\\PP_2D\\"
path_PP_D = "\\PP\\PP_3D\\"



#oms high / entry ,  1-entry 2-min 3-max
version = 1

#formate of output PP images , 0 for Qvga , 1 for vga
IsVga = 0

#keep intermediate raw and pp images - 1-yes , 0-no
keep_op = 0

#Image data VGA(for input images)
ip_h = 480
ip_w = 640
ip_bf = ip_h * ip_w *2


#for output images
if IsVga == 1 :
    height = 480
    width= 640
    buffersize = height * width * 2
else :
    height =240
    width = 320
    buffersize = height * width * 2

#report
Report_path = ""
Report_Image_Compare = "Image_COmpare.xlsx"

#referance file - static - need to add as input 
ref_file = ""
path_to_calib = "\\0000000000\\omscal_extrinsic_*.bin"




