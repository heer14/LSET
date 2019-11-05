import ctypes
class preprocessing :
    lib = ""
    DLL_InitializePreProcessing_core_Entry = ""
    DLL_InitializePreProcessing_core_High = ""
    DLL_LoadRaw = ""
    DLL_Preprocessing_core_PL_VGA = ""
    DLL_Preprocessing_core_PL = ""
    DLL_SaveRaw = ""
    
    def __init__(self , PreprocessingDLL) :
        self.lib = ctypes.WinDLL(PreprocessingDLL)
        self.DLL_InitializePreProcessing_core_Entry = self.lib["?InitializePreProcessing_core@offline@@YA?AW4ErrorList@@PEADW4APVersion@1@@Z"]
        self.DLL_LoadRaw = self.lib["?LoadRaw@offline@@YAHPEBDPEADH@Z"]
        self.DLL_Preprocessing_core_PL_VGA = self.lib["?Preprocessing_core_PL_VGA@offline@@YAHPEAG000I@Z"]
        self.DLL_SaveRaw = self.lib["?SaveRaw@offline@@YAHPEBDPEADH@Z"]
        self.DLL_Preprocessing_core_PL = self.lib["?Preprocessing_core_PL@offline@@YAHPEAG000I@Z"]
        self.DLL_InitializePreProcessing_core_High = self.lib["?InitializePreProcessing_core@offline@@YA?AW4ErrorList@@PEADIW4APVersion@1@@Z"]
        
    def InitializePreProcessing_core(self , path_for_Init_preprocessing_core) :
        ret = self.DLL_InitializePreProcessing_core_Entry(path_for_Init_preprocessing_core )
        return ret
    #not using
    def InitializePreProcessing_core_High(self , path_for_Init_preprocessing_core , nCameras ) :
        ret = self.DLL_InitializePreProcessing_core_High(path_for_Init_preprocessing_core , nCameras)
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