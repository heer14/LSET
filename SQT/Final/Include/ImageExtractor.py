import subprocess
import os
import re
from Config import config as cfg
from pathlib import Path

class ImageExtractor:
    input_dat = ""
    output_dir = ""
    image_extractor = ""
    database = ""
    videoId = ""
    UnifiedSDKversion = ""  
    VehicleLine = ""
    SteeringWhlPos = ""
    TransmissionType = ""
    RoofStyle = ""
    DisplaySize = ""

    def __init__(self , InPath , ImgExtPath , OutDir) :
        self.input_dat = InPath
        self.output_dir = OutDir
        self.image_extractor = ImgExtPath
    
    def Extract_Dat_info(self) :
        fname = os.path.basename(self.input_dat) 
        pat = re.search("(.*)__(.*)__(.*)__(.*)_(.*)_(.*)_(.*)_(.*).dat",fname)
        self.database = pat.group(1) 
        self.videoId =  pat.group(2)
        self.UnifiedSDKversion = pat.group(3)
        self.VehicleLine = pat.group(4)
        self.SteeringWhlPos = pat.group(5)
        self.TransmissionType = pat.group(6) 
        self.RoofStyle = pat.group(7)
        self.DisplaySize = pat.group(8)
        cfg.Report_Image_Compare = "ImageCompare_"+self.database+"_"+self.videoId
        cfg.Report_Image_Compare = cfg.Report_Image_Compare +".xlsx"
    
    def Resolve(self) :
        input_dat = Path(self.input_dat).resolve()
        image_extractor = Path(self.image_extractor).resolve()
        output_dir = Path(self.output_dir).resolve() 
        if not input_dat.exists():
            return 1
        if not image_extractor.exists():
            return 2
        if not output_dir.exists():
           return 3
        return 0
    
    def Run(self) :
        ret = subprocess.run([str(self.image_extractor), '-i', str(self.input_dat), '-o', str(self.output_dir)])
        return ret
        
            