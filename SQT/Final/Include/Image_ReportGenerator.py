import xlsxwriter

class ReportGenerator : 

    wb = ""
    version = ""
    TOLERANCE_PIXEL_WISE_DIFF = ""
    TOLERANCE_DIFF_PIXELS = ""

    path = ""
    used_dat_file = ""
    test_2d = ""
    test_3d = ""
    #ws_2D = ""
    ws_3D = ""
    ws_3D_1 = ""
    #ws_2D_1 = ""
    error = 0 
    ws_result = ""
    reporter = "Hiral Shah (hiral.sanjaybhaishah@lge.com)"
    #cur_index_2D = 3
    cur_index_3D = 3
    #cur_index_2D_1 = 3
    cur_index_3D_1 = 3
    cellfmt_bold = ""
    cellfmt_wrong = ""
    cellfmt_normal = ""
    cellfmt_normal_left = ""
    cellfmt_success = ""
    cellfmt_NF = ""
    cellfmt_warn = ""
    cellfmt_merge = ""
    cellfmt_Table = ""
    cellfmt_Table2 = ""
    
    def __init__(self , dat_file , test_2d , test_3d , user , error , version , TOLERANCE_PIXEL_WISE_DIFF , TOLERANCE_DIFF_PIXELS ) :
        self.used_dat_file = dat_file
        self.test_2d = test_2d
        self.test_3d = test_3d
        self.version = version
        self.error = error
        
        self.TOLERANCE_PIXEL_WISE_DIFF = TOLERANCE_PIXEL_WISE_DIFF
        self.TOLERANCE_DIFF_PIXELS = TOLERANCE_DIFF_PIXELS

        if user is not None :
            self.reporter = user


    def init_workbook(self , sztimeFormat) :
        self.addInformationSheet(sztimeFormat) 
        self.create_worksheet()
        self.set_header()

    def set_workbook_path(self , path) :
        self.wb = xlsxwriter.Workbook(path)
        self.path = path
        self.cellfmt_bold = self.wb.add_format({'bold': True, 'border':2, 'bg_color':'#D9D9D9', 'align':'center' , 'text_wrap': True})
        self.cellfmt_wrong = self.wb.add_format({'bg_color': '#ffcccc' ,'text_wrap': True , 'border':1 })
        self.cellfmt_normal = self.wb.add_format({'border':1 ,'text_wrap': True })
        self.cellfmt_normal_left = self.wb.add_format({'border':1, 'align':'left','text_wrap': True} )
        self.cellfmt_success = self.wb.add_format({'text_wrap': True , 'border':1 })
        self.cellfmt_success.set_font_color("'#32CD32'")
        self.cellfmt_NF = self.wb.add_format({'bg_color': '#ffcccc' ,'text_wrap': True , 'border':1 })
        self.cellfmt_NF.set_font_color("#FF0000")
        self.cellfmt_warn = self.wb.add_format({'font_name':"Arial Unicode MS","underline":True, "font_color":"#FF0000", "font_size":12 })
        self.cellfmt_Table = self.wb.add_format({"font_name": "Arial Unicode MS", "font_size": 11, "font_color": "#FFFFFF", "bold": True,"bg_color": "#002060", "align":"center", "valign":"vcenter"})
        self.cellfmt_merge = self.wb.add_format({"font_name":"Arial Unicode MS" , "font_size":20, "align":"center", "valign":"vcenter"})
        self.cellfmt_Table2 = self.wb.add_format({"font_name": "Arial Unicode MS", "font_size": 11, "border": 1, "align":"center", "valign":"vcenter"})
   
    def create_worksheet(self) :
        self.ws_result = self.wb.add_worksheet("Summary")
        '''
        self.ws_2D = self.wb.add_worksheet("2D")
        self.ws_2D.set_column(1, 1, 30)
        self.ws_2D.set_column(2, 2, 50)
        self.ws_2D.set_column(3,3,20)
        self.ws_2D.set_column(4,4,10)
        self.ws_2D.set_column(6,6,25)
        '''
        self.ws_3D = self.wb.add_worksheet("3D")
        self.ws_3D.set_column(1, 1, 30)
        self.ws_3D.set_column(2, 2, 30)
        self.ws_3D.set_column(3,3,20)
        self.ws_3D.set_column(4,5,10)
        self.ws_3D.set_column(6,6,25)
        self.ws_3D.set_column(7,7,25)
        
        if self.version == "Min" : 
            '''
            self.ws_2D_1 = self.wb.add_worksheet("2D_1")
            self.ws_2D_1.set_column(1, 1, 30)
            self.ws_2D_1.set_column(2, 2, 50)
            self.ws_2D_1.set_column(3,3,20)
            self.ws_2D_1.set_column(4,4,10)
            self.ws_2D_1.set_column(6,6,25)
            '''
            self.ws_3D_1 = self.wb.add_worksheet("3D_1")
            self.ws_3D_1.set_column(1, 1, 30)
            self.ws_3D_1.set_column(2, 2, 50)
            self.ws_3D_1.set_column(3,3,20)
            self.ws_3D_1.set_column(4,4,10)
            self.ws_3D_1.set_column(6,6,25)
            self.ws_3D_1.set_column(7,7,25)

    def Result_sheet(self) :
        self.ws_result.set_column(0, 0, 60)
        self.ws_result.set_column(1, 1, 30)
        '''
        self.ws_result.merge_range('A2:B2', 'Merged Range', self.cellfmt_merge)
        self.ws_result.write('A2' , "For 2D image Frames" , self.cellfmt_bold)
        '''
        self.ws_result.merge_range('A2:B2', 'Merged Range', self.cellfmt_merge)
        self.ws_result.write('A2' , "For 3D image Frames " , self.cellfmt_bold)
        '''
        self.ws_result.write('A3', "Pass : " , self.cellfmt_Table2)
        self.ws_result.write_formula('B3', '=COUNTIF(\'2D\'!G:G, "MATCHED")' , self.cellfmt_Table2) 
        self.ws_result.write('A4', "Fail : ", self.cellfmt_Table2 )
        self.ws_result.write_formula('B4', '=COUNTIF(\'2D\'!G:G, "NOT MATCHED")', self.cellfmt_Table2)
        self.ws_result.write('A5', "Frame Not Found : " , self.cellfmt_Table2 )
        self.ws_result.write_formula('B5', '=COUNTIF(\'2D\'!G:G, "Frame Not Found")'  , self.cellfmt_Table2)
        self.ws_result.write('A6', "Total : " , self.cellfmt_Table2)
        self.ws_result.write_formula('B6', '=COUNTA(\'2D\'!A:A)-1', self.cellfmt_Table2)
        '''
        self.ws_result.write('A3', "Pass : " , self.cellfmt_Table2)
        self.ws_result.write_formula('B3', '=COUNTIF(\'3D\'!H:H, "MATCHED")'  , self.cellfmt_Table2)
        self.ws_result.write('A4', "Fail : ", self.cellfmt_Table2 )
        self.ws_result.write_formula('B4', '=COUNTIF(\'3D\'!H:H, "NOT MATCHED")' , self.cellfmt_Table2)
        self.ws_result.write('A5', "Frame Not Found : " , self.cellfmt_Table2 )
        self.ws_result.write_formula('B5', '=COUNTIF(\'3D\'!G:G, "Frame Not Found")'  , self.cellfmt_Table2)
        self.ws_result.write('A6', "Total : " , self.cellfmt_Table2)
        self.ws_result.write_formula('B6', '=COUNTA(\'3D\'!A:A)-1'  , self.cellfmt_Table2)
        
        if self.version == "Min" : 
            '''
            self.ws_result.merge_range('A14:B14', 'Merged Range', self.cellfmt_merge)
            self.ws_result.write('A14' , "For 2D image Frames (Cam 1) " , self.cellfmt_bold)
            '''
            self.ws_result.merge_range('A8:B8', 'Merged Range', self.cellfmt_merge)
            self.ws_result.write('A8' , "For 3D image Frames (Cam 1)" , self.cellfmt_bold)
            '''
            self.ws_result.write('A15', "Pass : " , self.cellfmt_Table2)
            self.ws_result.write_formula('B15', '=COUNTIF(\'2D_1\'!G:G, "MATCHED")' , self.cellfmt_Table2) 
            self.ws_result.write('A16', "Fail : ", self.cellfmt_Table2 )
            self.ws_result.write_formula('B16', '=COUNTIF(\'2D_1\'!G:G, "NOT MATCHED")', self.cellfmt_Table2)
            self.ws_result.write('A17', "Frame Not Found : " , self.cellfmt_Table2 )
            self.ws_result.write_formula('B17', '=COUNTIF(\'2D_1\'!G:G, "Frame Not Found")'  , self.cellfmt_Table2)
            self.ws_result.write('A18', "Total : " , self.cellfmt_Table2)
            self.ws_result.write_formula('B18', '=COUNTA(\'2D_1\'!A:A)-1', self.cellfmt_Table2)
            '''
            self.ws_result.write('A9', "Pass : " , self.cellfmt_Table2)
            self.ws_result.write_formula('B9', '=COUNTIF(\'3D_1\'!H:H, "MATCHED")'  , self.cellfmt_Table2)
            self.ws_result.write('A10', "Fail : ", self.cellfmt_Table2 )
            self.ws_result.write_formula('B10', '=COUNTIF(\'3D_1\'!H:H, "NOT MATCHED")' , self.cellfmt_Table2)
            self.ws_result.write('A11', "Frame Not Found : " , self.cellfmt_Table2 )
            self.ws_result.write_formula('B11', '=COUNTIF(\'3D_1\'!H:H, "Frame Not Found")'  , self.cellfmt_Table2)
            self.ws_result.write('A12', "Total : " , self.cellfmt_Table2)
            self.ws_result.write_formula('B12', '=COUNTA(\'3D_1\'!A:A)-1'  , self.cellfmt_Table2)
        
    
    def set_header(self) : 
        
        '''
        self.ws_2D.write('A1' , 'Sr_No' ,self.cellfmt_bold  )
        self.ws_2D.write('B1' , 'SQT processed Image' ,self.cellfmt_bold  )
        self.ws_2D.write('C1' , 'Automated Output Image',self.cellfmt_bold )
        self.ws_2D.write('D1' , 'Time stamp',self.cellfmt_bold  )
        self.ws_2D.write('E1' , 'Frame Count(hex)',self.cellfmt_bold  )
        self.ws_2D.write('F1' , 'Error % ', self.cellfmt_bold  )
        self.ws_2D.write('G1' , 'Result', self.cellfmt_bold  )
        '''
        self.ws_3D.write('A1' , 'Sr_No' ,self.cellfmt_bold  )
        self.ws_3D.write('B1' , 'SQT processed Image' ,self.cellfmt_bold  )
        self.ws_3D.write('C1' , 'Automated Output Image',self.cellfmt_bold )
        self.ws_3D.write('D1' , 'Time stamp',self.cellfmt_bold  )
        self.ws_3D.write('E1' , 'Frame Count(hex)',self.cellfmt_bold  )
        self.ws_3D.write('F1' , 'no of bits not matching', self.cellfmt_bold  )
        self.ws_3D.write('G1' , 'Error % ', self.cellfmt_bold  )
        self.ws_3D.write('H1' , 'Result', self.cellfmt_bold  )    
        if self.version == "Min" :
            '''
            self.ws_2D_1.write('A1' , 'Sr_No' ,self.cellfmt_bold  )
            self.ws_2D_1.write('B1' , 'SQT processed Image' ,self.cellfmt_bold  )
            self.ws_2D_1.write('C1' , 'Automated Output Image',self.cellfmt_bold )
            self.ws_2D_1.write('D1' , 'Time stamp',self.cellfmt_bold  )
            self.ws_2D_1.write('E1' , 'Frame Count(hex)',self.cellfmt_bold  )
            self.ws_2D_1.write('F1' , 'Error % ', self.cellfmt_bold  )
            self.ws_2D_1.write('G1' , 'Result', self.cellfmt_bold  )
            '''
            self.ws_3D_1.write('A1' , 'Sr_No' ,self.cellfmt_bold  )
            self.ws_3D_1.write('B1' , 'SQT processed Image' ,self.cellfmt_bold  )
            self.ws_3D_1.write('C1' , 'Automated Output Image',self.cellfmt_bold )
            self.ws_3D_1.write('D1' , 'Time stamp',self.cellfmt_bold  )
            self.ws_3D_1.write('E1' , 'Frame Count(hex)',self.cellfmt_bold  )
            self.ws_3D_1.write('F1' , 'no of bits not matching', self.cellfmt_bold  )
            self.ws_3D_1.write('G1' , 'Error % ', self.cellfmt_bold  )
            self.ws_3D_1.write('H1' , 'Result', self.cellfmt_bold  )  
    
    def add_data(self ,type, image1 , image2 , time , fc, result , NoOfBits) :
        if result != "Frame NOT Found" :
            if (result <= self.error) :
                format = self.cellfmt_success
            else :
                format = self.cellfmt_wrong
            
        else :
            format = self.cellfmt_NF
        
        '''
        if (type == "2D") :
            ws = self.ws_2D
            cur_index = self.cur_index_2D
            self.cur_index_2D = self.cur_index_2D+1
        '''    
        if(type == "3D") :          
            ws = self.ws_3D
            cur_index = self.cur_index_3D
            self.cur_index_3D = self.cur_index_3D+1
        
        elif(type == "3D1") :          
            ws = self.ws_3D_1
            cur_index = self.cur_index_3D_1
            self.cur_index_3D_1 = self.cur_index_3D_1 +1
        '''
        elif(type == "2D1") :          
            ws = self.ws_2D_1
            cur_index = self.cur_index_2D_1
            self.cur_index_2D_1 = self.cur_index_2D_1 +1
        '''   
        ws.write('A'+str(cur_index) , cur_index-2 ,self.cellfmt_normal_left )
        ws.write('B'+str(cur_index) , image1 , format)
        ws.write('C'+str(cur_index) , image2 , format)
        ws.write('D'+str(cur_index) , time, format)
        ws.write('E'+str(cur_index) , fc, format )

        
        if result != "Frame NOT Found" :
            ws.write('F' + str(cur_index) , NoOfBits , format )
            ws.write('G'+str(cur_index) , result, format)
            ws.write_formula( 'H'+str(cur_index) , "=IF(F"+str(cur_index)+"<="+str(self.error)+",\"MATCHED\",\"NOT MATCHED\")" , format)
        else :
            ws.write('F'+str(cur_index) , "N/A", format)
            ws.write('G'+str(cur_index) , result, format)
            ws.write('H'+str(cur_index) , "N/A", format)
   
    
    def close(self ) :
        self.Result_sheet()
        self.wb.close()
        print("Image compare report has been made available at " +self.path)
  
    def addInformationSheet(self , sztimeFormat ):
        strWarning = "LGE/DAI Internal Use Only"
        strTitle = "OMS System Qualification Test Automation Phase1 Report"
        infoSheet = self.wb.add_worksheet("Information")
        # set column size
        infoSheet.set_column(0, 0, 30)
        infoSheet.set_column(1, 1, 60)
        infoSheet.set_column(2, 2, 30)
        # set row size
        infoSheet.set_row(1, 29.25)
        infoSheet.set_row(3, 26.25)
        infoSheet.set_row(4, 26.25)
        infoSheet.set_row(5, 26.25)
        infoSheet.set_row(6, 26.25)
        infoSheet.set_row(7, 26.25)
        infoSheet.set_row(8, 26.25)
        infoSheet.set_row(9, 26.25)
        infoSheet.set_row(10, 26.25)
        infoSheet.set_row(11, 26.25)
        infoSheet.set_row(12, 26.25)


        infoSheet.write("A1", strWarning, self.cellfmt_warn)
        infoSheet.merge_range('A2:C2', 'Merged Range', self.cellfmt_merge)
        infoSheet.write('A2', strTitle , self.cellfmt_merge)
        infoSheet.write('A4', "Item", self.cellfmt_Table)
        infoSheet.write('B4', "Values", self.cellfmt_Table)
        infoSheet.write('C4', "Notes", self.cellfmt_Table)
        
        infoSheet.write('A5', "Reporter", self.cellfmt_Table2)
        infoSheet.write('B5', self.reporter, self.cellfmt_Table2)
        infoSheet.write('C5', "", self.cellfmt_Table2)

        infoSheet.write('A6', "Date", self.cellfmt_Table2)
        infoSheet.write('B6', sztimeFormat, self.cellfmt_Table2)
        infoSheet.write('C6', "", self.cellfmt_Table2)

        infoSheet.write('A7', "Used DAT file", self.cellfmt_Table2)
        infoSheet.write('B7', self.used_dat_file, self.cellfmt_Table2)
        infoSheet.write('C7', "", self.cellfmt_Table2)
        
        infoSheet.write('A8', "Path to Test files 2D", self.cellfmt_Table2)
        infoSheet.write('B8', self.test_2d, self.cellfmt_Table2)
        infoSheet.write('C8', "", self.cellfmt_Table2)

        infoSheet.write('A9', "path to Test files 3D", self.cellfmt_Table2)
        infoSheet.write('B9', self.test_3d, self.cellfmt_Table2)
        infoSheet.write('C9', "", self.cellfmt_Table2)

        infoSheet.write('A10', "TOLERANCE_DIFF_PIXELS", self.cellfmt_Table2)
        infoSheet.write('B10', self.TOLERANCE_DIFF_PIXELS, self.cellfmt_Table2)
        infoSheet.write('C10', "", self.cellfmt_Table2)

        
        infoSheet.write('A11', "TOLERANCE_PIXEL_WISE_DIFF", self.cellfmt_Table2)
        infoSheet.write('B11', self.TOLERANCE_PIXEL_WISE_DIFF, self.cellfmt_Table2)
        infoSheet.write('C11', "", self.cellfmt_Table2)