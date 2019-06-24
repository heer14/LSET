import os
import shutil
RootDir1 = r'E:\Study\OOAD'
TargetFolder = r'E:\Study\SA\YouTubePPT'
for root, dirs, files in os.walk((os.path.normpath(RootDir1)), topdown=False):
        for name in files:
            if name.endswith('.pptx'):
                print ("Found")
                SourceFolder = os.path.join(root,name)
                shutil.copy2(SourceFolder, TargetFolder) #copies csv to new folder