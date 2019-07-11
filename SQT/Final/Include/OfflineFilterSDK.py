import ctypes
class preprocessing :
    lib = ""
    InitializePreProcessing_core_Entry_ = ""
    InitializePreProcessing_core_High_ = ""
    LoadRaw_ = ""
    Preprocessing_core_PL_VGA_ = ""
    Preprocessing_core_PL_ = ""
    SaveRaw_ = ""
    
    def __init__(self , PreprocessingDLL) :
        self.lib = ctypes.WinDLL(PreprocessingDLL)
        self.InitializePreProcessing_core_Entry_ = self.lib["?InitializePreProcessing_core@offline@@YA?AW4ErrorList@@PEADW4APVersion@1@@Z"]
        self.LoadRaw_ = self.lib["?LoadRaw@offline@@YAHPEBDPEADH@Z"]
        self.Preprocessing_core_PL_VGA_ = self.lib["?Preprocessing_core_PL_VGA@offline@@YAHPEAG000I@Z"]
        self.SaveRaw_ = self.lib["?SaveRaw@offline@@YAHPEBDPEADH@Z"]
        self.Preprocessing_core_PL_ = self.lib["?Preprocessing_core_PL@offline@@YAHPEAG000I@Z"]
        self.InitializePreProcessing_core_High_ = self.lib["?InitializePreProcessing_core@offline@@YA?AW4ErrorList@@PEADIW4APVersion@1@@Z"]
        
    def InitializePreProcessing_core_Entry(self , path_for_Init_preprocessing_core) :
        ret = self.InitializePreProcessing_core_Entry_(path_for_Init_preprocessing_core)
        return ret
    
    def InitializePreProcessing_core_High(self , path_for_Init_preprocessing_core , nCameras ) :
        ret = self.InitializePreProcessing_core_High_(path_for_Init_preprocessing_core , nCameras)
        return ret    
    
    def LoadRaw(self , path , buffer , B_Size) :
        ret = self.LoadRaw_(path, buffer.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) ,B_Size)
        return ret
    
    def Preprocessing_core_PL_VGA(self , InDepth ,OutDepth ,InIR ,ResizeIR , camIndex) :
        ret = self.Preprocessing_core_PL_VGA_(InDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , InIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , camIndex )
        return ret
        
    def Preprocessing_core_PL_QVGA(self , InDepth ,OutDepth ,InIR ,ResizeIR , camIndex) :
        ret = self.Preprocessing_core_PL_(InDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , InIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , ResizeIR.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , camIndex )
        return ret
    
    def SaveRaw(self , path_out , OutDepth , B_Size) : 
        ret = self.SaveRaw_(path_out , OutDepth.ctypes.data_as(ctypes.POINTER(ctypes.c_int16)) , B_Size )
        return ret