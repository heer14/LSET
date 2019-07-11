
import numpy as np
class ImageCompare:
    def Get_Error(self , Image1 , Image2) :
        error = np.mean(Image1 != Image2)
        return (error)
    
    def Get_mse(self , Image1 , Image2) :
        mse = (np.square(Image1 - Image2)).mean(axis=None)
        return (mse)