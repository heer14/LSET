import xlsxwriter

class ReportGenerator : 

    wb = ""
    path = ""
    ws_2D = ""
    cur_index_2D = 3
    cur_index_3D = 3
    cellfmt_bold = ""
    cellfmt_wrong = ""
    cellfmt_normal = ""
    cellfmt_normal_left = ""
    cellfmt_sucess = ""
    cellfmt_NF = ""
    
    def set_workbook_path(self , path) :
        self.wb = xlsxwriter.Workbook(path)
        self.path = path
        self.cellfmt_bold = self.wb.add_format({'bold': True, 'border':1, 'bg_color':'#D9D9D9', 'align':'center' , 'text_wrap': True})
        self.cellfmt_wrong = self.wb.add_format({'bg_color': '#ffcccc' ,'text_wrap': True , 'border':1 })
        self.cellfmt_normal = self.wb.add_format({'border':1 ,'text_wrap': True })
        self.cellfmt_normal_left = self.wb.add_format({'border':1, 'align':'left','text_wrap': True} )
        self.cellfmt_sucess = self.wb.add_format({'text_wrap': True , 'border':1 })
        self.cellfmt_sucess.set_font_color("'#32CD32'")
        self.cellfmt_NF = self.wb.add_format({'bg_color': '#ffcccc' ,'text_wrap': True , 'border':1 })
        self.cellfmt_NF.set_font_color("#FF0000")
        
    
    def create_worksheet(self) :
        self.ws_2D = self.wb.add_worksheet("2D")
        self.ws_2D.set_column(1, 1, 30)
        self.ws_2D.set_column(2, 2, 50)
        self.ws_2D.set_column(3,3,20)
        self.ws_2D.set_column(4,4,10)
        self.ws_3D = self.wb.add_worksheet("3D")
        self.ws_3D.set_column(1, 1, 30)
        self.ws_3D.set_column(2, 2, 50)
        self.ws_3D.set_column(3,3,20)
        self.ws_3D.set_column(4,4,10)
        
    def set_header(self) : 
        self.ws_2D.write('A1' , 'Sr_No' ,self.cellfmt_bold  )
        self.ws_2D.write('B1' , 'SQT processed Image' ,self.cellfmt_bold  )
        self.ws_2D.write('C1' , 'Automated Output Image',self.cellfmt_bold )
        self.ws_2D.write('D1' , 'Time stamp',self.cellfmt_bold  )
        self.ws_2D.write('E1' , 'Frame Count(hex)',self.cellfmt_bold  )
        self.ws_2D.write('F1' , 'Result', self.cellfmt_bold  )
        self.ws_3D.write('A1' , 'Sr_No' ,self.cellfmt_bold  )
        self.ws_3D.write('B1' , 'SQT processed Image' ,self.cellfmt_bold  )
        self.ws_3D.write('C1' , 'Automated Output Image',self.cellfmt_bold )
        self.ws_3D.write('D1' , 'Time stamp',self.cellfmt_bold  )
        self.ws_3D.write('E1' , 'Frame Count(hex)',self.cellfmt_bold  )
        self.ws_3D.write('F1' , 'Result(Error % )', self.cellfmt_bold  )
    
    def add_data(self ,type, image1 , image2 , time , fc, result) :
        if result != "Not Found" :
            if (result == 0) :
                format = self.cellfmt_sucess
            else :
                format = self.cellfmt_wrong
            
        else :
            format = self.cellfmt_NF
        if (type == "2D") :
            ws = self.ws_2D
            cur_index = self.cur_index_2D
            self.cur_index_2D = self.cur_index_2D+1
            
        elif(type == "3D") :
            ws = self.ws_3D
            cur_index = self.cur_index_3D
            self.cur_index_3D = self.cur_index_3D+1
           
        ws.write('A'+str(cur_index) , cur_index-2 ,self.cellfmt_normal_left )
        ws.write('B'+str(cur_index) , image1 , format)
        ws.write('C'+str(cur_index) , image2 , format)
        ws.write('D'+str(cur_index) , time, format)
        ws.write('E'+str(cur_index) , fc, format )
        ws.write('F'+str(cur_index) , result, format)
   
    
    
    def close(self) :
        print("Image compare report has been made available at " +self.path)
        self.wb.close()
  
