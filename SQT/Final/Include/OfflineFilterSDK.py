import ctypes
import numpy as np
from numpy.ctypeslib import ndpointer

class preprocessing :
    lib = ""
    DLL_InitializePreProcessing_core_Entry = ""
    DLL_InitializePreProcessing_core_High = ""
    DLL_LoadRaw = ""
    DLL_Preprocessing_core_PL_VGA = ""
    DLL_Preprocessing_core_PL = ""
    DLL_SaveRaw = ""
    DLL_getXYZ = ""
    DLL_getRTmatrix = ""
    RTmatrix = np.zeros(12 ,dtype=np.float32 )
    DLL_set_FlipMode = ""
    
    def __init__(self , PreprocessingDLL , version) :
        self.lib = ctypes.WinDLL(PreprocessingDLL)
        self.DLL_InitializePreProcessing_core_Entry = self.lib["?InitializePreProcessing_core@offline@@YA?AW4ErrorList@@PEADW4APVersion@1@@Z"]
        self.DLL_LoadRaw = self.lib["?LoadRaw@offline@@YAHPEBDPEADH@Z"]
        self.DLL_Preprocessing_core_PL_VGA = self.lib["?Preprocessing_core_PL_VGA@offline@@YAHPEAG000I@Z"]
        self.DLL_SaveRaw = self.lib["?SaveRaw@offline@@YAHPEBDPEADH@Z"]
        self.DLL_Preprocessing_core_PL = self.lib["?Preprocessing_core_PL@offline@@YAHPEAG000I@Z"]
        self.DLL_InitializePreProcessing_core_High = self.lib["?InitializePreProcessing_core@offline@@YA?AW4ErrorList@@PEADIW4APVersion@1@@Z"]
        self.DLL_set_FlipMode = self.lib["?SetFlipMode@offline@@YAXH@Z"]
        if version == 1 : 
            self.DLL_getXYZ = self.lib["?GetFilteredPointCloudPatch_new@offline@@YA?AW4ErrorList@@PEAG0PEAM11GGGG1HHH@Z"]
            self.DLL_getRTmatrix = self.lib["?GetRTMatrix@offline@@YA_NPEBDQEAM@Z"]
            self.DLL_getXYZ.argtypes = [ctypes.POINTER(ctypes.c_int16), 
					ctypes.POINTER(ctypes.c_int16) , 
					ctypes.POINTER(ctypes.c_float) ,
					ctypes.POINTER(ctypes.c_float),
					ctypes.POINTER(ctypes.c_float), 
					ctypes.c_uint16 , 
					ctypes.c_uint16  , 
					ctypes.c_uint16 , 
					ctypes.c_uint16  ,
					ndpointer(ctypes.c_float ) , 
					ctypes.c_int32 ,  
					ctypes.c_int32 , 
					ctypes.c_int32  ]

    def InitializePreProcessing_core(self , path_for_Init_preprocessing_core , version) :
        ret = self.DLL_InitializePreProcessing_core_High(path_for_Init_preprocessing_core , ctypes.c_int(1) , version)
        return ret

    def setFlipMode(self , Mode ) :
        ret = self.DLL_set_FlipMode(Mode)
        return ret 

    #not using
    def InitializePreProcessing_core_High(self , path_for_Init_preprocessing_core , nCameras , version ) :
        ret = self.DLL_InitializePreProcessing_core_High(path_for_Init_preprocessing_core , nCameras , version )
        return ret    
    
    def LoadRaw(self , path , Image_Buffer , B_Size) :
        ret = self.DLL_LoadRaw(path, Image_Buffer , ctypes.c_int(B_Size))
        return ret
    
    def Preprocessing_core_PL_VGA(self , InDepth ,OutDepth ,InIR ,ResizeIR , cam_Index ) :
        ret = self.DLL_Preprocessing_core_PL_VGA(InDepth ,OutDepth ,InIR ,ResizeIR, ctypes.c_int32(cam_Index))
        return ret
        
    def Preprocessing_core_PL(self , InDepth ,OutDepth ,InIR ,ResizeIR , cam_Index) :
        ret = self.DLL_Preprocessing_core_PL(InDepth ,OutDepth ,InIR ,ResizeIR, ctypes.c_int32(cam_Index) )
        return ret
    
    def SaveRaw(self , path_out , OutDepth , B_Size) : 
        ret = self.DLL_SaveRaw(path_out , OutDepth , ctypes.c_int(B_Size))
        return ret

    def GetRTMatrix(self , path_to_calibration ) :
        #RTmatrix = np.zeros(12 ,dtype=np.float32 )
        ret = self.DLL_getRTmatrix(ctypes.c_char_p(path_to_calibration) ,self.RTmatrix.ctypes.data_as(ctypes.POINTER(ctypes.c_float)) )
        self.RTmatrix = self.RTmatrix * 1000
        print(self.RTmatrix)
        return ret
    
    def getXYZ(self ,Depth , Ir , data_dict ) :
        ret = self.DLL_getXYZ(  Depth , Ir ,
			data_dict['x'],
			data_dict['y'],
			data_dict['z'],
			data_dict['patch_y'],
			data_dict['patch_x'],
			data_dict['patch_h'] , 
			data_dict['patch_w'] , 
            self.RTmatrix ,
            data_dict['width'], 
            data_dict['height'],
            data_dict['camera'] )
        #print(data_dict['x'])
        return ret 