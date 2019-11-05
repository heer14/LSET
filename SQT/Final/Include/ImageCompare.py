
import numpy as np
from Config import config as cfg

class ImageCompare:
    def Get_Error(self , Image1 , Image2) :
        error = np.mean(Image1 != Image2)
        return (error)
    
    def Get_mse(self , Image1 , Image2) :
        mse = (np.square(Image1 - Image2)).mean(axis=None)
        return (mse)

    def bit_by_bit (self , Image1 , Image2 , height , width ) :
        error = 0
        cnt = 0
        for x in range(1 , width-1) :
            for y in range(0,height-1) :
                if( (abs(Image1[x][y] - Image2[x][y] ))> cfg.TOLERANCE_PIXEL_WISE_DIFF ) :
                    cnt = cnt + 1
                    
        error =  100 * cnt 
        error = error / ((width-1)*height)
        return (round(error , 2) , cnt)