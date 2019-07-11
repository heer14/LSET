

#Input Path for DAT
input_dat_path = ""

#Image Comparator test data (from Actual SQT process)
path_test_2D = ""
path_test_3D = ""

#set env
image_extractor_path = "ImageExtractor\\ImageExtractor.exe"
Unprocessed_raw_Images = "Output" 
PreprocessingDLL = "OfflineFilterSDK.dll"
path_to_Bin = "Output\\0000000000\\"

# Raw Images
path_raw =  "Output\\0000000000\\"
path_raw_A = "Output\\0000000000\\IR\\"
path_raw_D = "Output\\0000000000\\Depth\\"

#preprocessed Images
path_PP =  "Output\\PP\\ "
path_PP_A = "Output\\PP\\PP_2D\\"
path_PP_D = "Output\\PP\\PP_3D\\"

#old_path
path_old = "BackUp\\output.zip"

#oms high / entry ,  0-entry 1-high
version = 1

vga = 0

#keep intermediate raw and pp images - 1-yes , 0-no
keep_op = 1

#Image data VGA(for input images)
ip_h = 480
ip_w = 640
ip_bf = ip_h * ip_w *2


#for output images
if version == 0 :
    height = 480
    width= 640
    buffersize = height * width * 2
else :
    height =240
    width = 320
    buffersize = height * width * 2

#report
Report_path = "Reports\\"
Report_Image_Compare = ""


