from ctypes import *
import ctypes
import numpy as np
from numpy.ctypeslib import ndpointer

InDepth = np.zeros(( 640 , 480) ,dtype=np.uint16 )
InIR = np.zeros((640 , 480) ,dtype=np.uint16 )
OutDepth = np.zeros((320 , 240) ,dtype=np.uint16 )
ResizeIR = np.zeros((320 , 240) ,dtype=np.uint16 )

lib = ctypes.WinDLL("D:\\Python\\Demo_Phase2\\OfflineFilterSDK.dll")
API = lib["?GetFilteredPointCloudPatch@offline@@YA?AW4ErrorList@@PEAG0PEAV?$vector@UPoint3Df_t@@V?$allocator@UPoint3Df_t@@@std@@@std@@GGGGPEAMHHGGH@Z"]

Init = lib["?InitializePreProcessing_core@offline@@YA?AW4ErrorList@@PEADIW4APVersion@1@@Z"]
path_to_Bin = b"D:\\Python\\Demo_Phase2\\Output\\coralprod180618_58\\0000000000\\"

ret = Init(path_to_Bin , ctypes.c_int(1) , ctypes.c_int(0xFFFFFFFD))
if ret == 0 :
    print("Init : Success ")

path_IR = b"D:\\Python\\Demo_Phase2\\Output\\coralprod180618_58\\0000000000\\IR\\000_0000_0000000000_A_2018_06_14_14_18_27_0000000000.raw"
path_depth =   b"D:\\Python\\Demo_Phase2\\Output\\coralprod180618_58\\0000000000\\Depth\\000_0000_0000000000_D_2018_06_14_14_18_27_0000000000.raw"

#Load raw depth and IR image
LoadRaw = lib["?LoadRaw@offline@@YAHPEBDPEADH@Z"]
ret = LoadRaw(path_depth , InDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) ,  640 * 480 *2)
if ret == 0 :
    print("Load raw : Success ")
ret = LoadRaw(path_IR , InIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , 640 * 480 *2)
if ret == 0 :
    print("Load raw : Success ")

print(InDepth)
print(InIR)

#preprocessing_pl

Preprocessing_core_PL = lib["?Preprocessing_core_PL@offline@@YAHPEAG000I@Z"]
ret = Preprocessing_core_PL(InDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)), OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , InIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , ctypes.c_int(0) )
if ret == 0 :
    print("Preprocessing  : Success ")
print(OutDepth)
print(ResizeIR)

path_extrin =b"D:\\Python\\Demo_Phase2\\Output\\coralprod180618_58\\0000000000\\omscal_extrinsic_0.bin"
RTmatrix = np.zeros((3,4) ,dtype=np.float32 )
getRTmatrix = lib["?GetRTMatrix@offline@@YA_NPEBDQEAM@Z"]
ret = getRTmatrix(ctypes.c_char_p(path_extrin) ,RTmatrix.ctypes.data_as(ctypes.POINTER(ctypes.c_float)) )

if ret == 0 :
    print("RT matrix : Success ")

RTmatrix = RTmatrix * 1000
print(RTmatrix)




class xyz(ctypes.Structure) :
    _fields_ = [
      ("x", c_float),
      ("y", c_float),
      ("z", c_float),
    ]

xyzObj = xyz(0 , 0 ,0)

xyzValues = np.zeros((1,3) , dtype = float)

API.argtypes = [ctypes.POINTER(ctypes.c_uint16), 
					ctypes.POINTER(ctypes.c_uint16) , 
					ctypes.POINTER(xyz),
					ctypes.c_uint16 , 
					ctypes.c_uint16  , 
					ctypes.c_uint16 , 
					ctypes.c_uint16  ,
					ctypes.POINTER(ctypes.c_float ),
                     ctypes.c_int32 ,
                     ctypes.c_int32 ,
                     ctypes.c_uint16 ,
                     ctypes.c_uint16 ,
                     ctypes.c_int32 ]


ret = API(OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_uint16)), 
              ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_uint16)) ,
        xyzObj ,
        218,
        182,
        1,
        1,
        RTmatrix.ctypes.data_as(ctypes.POINTER(ctypes.c_float)) , 
        640 , 
        480 , 
        0 , 
        4000 ,
         1 )



print(ret)
print(xyzObj.x)
print(xyzObj.y)
print(xyzObj.z)



