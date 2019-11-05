import xlsxwriter
import sys

class ReportGenerator : 

    wb = ""
    version = ""
    path = ""
    used_Calibration_file = ""

    ws_ITGC_D_Hand1 = ""
    ws_ITGC_D_Hand1_FT = ""
    ws_ITGC_D_Hand2 = ""
    ws_ITGC_D_Hand2_FT = ""
    ws_ITGC_P_Hand1 = ""
    ws_ITGC_P_Hand1_FT = ""
    ws_ITGC_P_Hand2 = ""
    ws_ITGC_P_Hand2_FT = ""

    ws_result = ""
    reporter = "Hiral Shah (hiral.sanjaybhaishah@lge.com)"
    cur_index_ITGC_D_Hand1 = 3
    cur_index_ITGC_D_Hand1_FT = 3
    cur_index_ITGC_D_Hand2 = 3
    cur_index_ITGC_D_Hand2_FT = 3
    cur_index_ITGC_P_Hand1 = 3
    cur_index_ITGC_P_Hand1_FT = 3
    cur_index_ITGC_P_Hand2 = 3
    cur_index_ITGC_P_Hand2_FT = 3
    
    cellfmt_bold = ""
    cellfmt_wrong = ""
    cellfmt_normal = ""
    cellfmt_normal_left = ""
    cellfmt_X_purple = ""
    cellfmt_Y_orange = ""
    cellfmt_Z_green = ""
    cellfmt_NF = ""
    cellfmt_warn = ""
    cellfmt_merge = ""
    cellfmt_Table = ""
    cellfmt_Table2 = ""
    
    def __init__(self , used_Calibration_file , user  , version ) :
        self.used_Calibration_file = used_Calibration_file
        self.version = version
    

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
        #self.cellfmt_wrong = self.wb.add_format({'bg_color': '#ffcccc' ,'text_wrap': True , 'border':1 })
        self.cellfmt_normal = self.wb.add_format({'border':1 ,'text_wrap': True })
        self.cellfmt_normal_left = self.wb.add_format({'border':1,'valign' : 'top' , 'align':'left','text_wrap': True} )
        self.cellfmt_X_purple = self.wb.add_format({'text_wrap': True , 'border':1 , "font_color":"#800080" , 'valign' : 'top' ,  'align':'left'})
        self.cellfmt_Y_orange = self.wb.add_format({'text_wrap': True , 'border':1 , "font_color":"#FFA500" , 'valign' : 'top' ,  'align':'left' })
        self.cellfmt_Z_green = self.wb.add_format({'text_wrap': True , 'border':1 , "font_color":"#008000" , 'valign' : 'top' ,  'align':'left' })
        self.cellfmt_warn = self.wb.add_format({'font_name':"Arial Unicode MS","underline":True, "font_color":"#FF0000", "font_size":12 })
        self.cellfmt_Table = self.wb.add_format({"font_name": "Arial Unicode MS", "font_size": 11, "font_color": "#FFFFFF", "bold": True,"bg_color": "#002060", "align":"center", "valign":"vcenter"})
        self.cellfmt_merge = self.wb.add_format({"font_name":"Arial Unicode MS" , "font_size":20, "align":"center", "valign":"vcenter"})
        self.cellfmt_Table2 = self.wb.add_format({"font_name": "Arial Unicode MS", "font_size": 11, "border": 1, "align":"center", "valign":"vcenter"})

    def create_worksheet(self) :

        self.ITGC_D_Hand1 = self.wb.add_worksheet("ITGC_D_Hand1")
        self.ITGC_D_Hand1.set_column(1,1,30)
        self.ITGC_D_Hand1.set_column(3,3,20)
        
        self.ITGC_D_Hand1_FT = self.wb.add_worksheet("ITGC_D_Hand1_FT")
        self.ITGC_D_Hand1_FT.set_column(1,1,30)
        self.ITGC_D_Hand1_FT.set_column(3,3,20)

        self.ITGC_D_Hand2 = self.wb.add_worksheet("ITGC_D_Hand2")
        self.ITGC_D_Hand2.set_column(1,1,30)
        self.ITGC_D_Hand2.set_column(3,3,20)

        self.ITGC_D_Hand2_FT = self.wb.add_worksheet("ITGC_D_Hand2_FT")
        self.ITGC_D_Hand2_FT.set_column(1,1,30)
        self.ITGC_D_Hand2_FT.set_column(3,3,20)

        self.ITGC_P_Hand1 = self.wb.add_worksheet("ITGC_P_Hand1")
        self.ITGC_P_Hand1.set_column(1,1,30)
        self.ITGC_P_Hand1.set_column(3,3,20)

        self.ITGC_P_Hand1_FT = self.wb.add_worksheet("ITGC_P_Hand1_FT")
        self.ITGC_P_Hand1_FT.set_column(1,1,30)
        self.ITGC_P_Hand1_FT.set_column(3,3,20)

        self.ITGC_P_Hand2 = self.wb.add_worksheet("ITGC_P_Hand2")
        self.ITGC_P_Hand2.set_column(1,1,30)
        self.ITGC_P_Hand2.set_column(3,3,20)

        self.ITGC_P_Hand2_FT = self.wb.add_worksheet("ITGC_P_Hand2_FT")
        self.ITGC_P_Hand2_FT.set_column(1,1,30)
        self.ITGC_P_Hand2_FT.set_column(3,3,20)
    
        
    
    def set_header(self) : 
        
        self.ITGC_D_Hand1.write('A1' , 'Sr_No' ,self.cellfmt_bold  )
        self.ITGC_D_Hand1.write('B1' , 'SQT processed Image' ,self.cellfmt_bold  )
        self.ITGC_D_Hand1.write('C1' , 'Frame Count',self.cellfmt_bold  )
        self.ITGC_D_Hand1.write('D1' , 'Time stamp',self.cellfmt_bold  )
        self.ITGC_D_Hand1.write('E1' , 'u', self.cellfmt_bold  )
        self.ITGC_D_Hand1.write('F1' , 'v', self.cellfmt_bold  )
        self.ITGC_D_Hand1.write('G1' , 'Expected x', self.cellfmt_bold  )
        self.ITGC_D_Hand1.write('H1' , 'Expected y', self.cellfmt_bold  )
        self.ITGC_D_Hand1.write('I1' , 'Expected z', self.cellfmt_bold  )
        self.ITGC_D_Hand1.write('J1' , 'Actual x', self.cellfmt_bold  )
        self.ITGC_D_Hand1.write('K1' , 'Actual y', self.cellfmt_bold  )
        self.ITGC_D_Hand1.write('L1' , 'Actual z', self.cellfmt_bold  )
        self.ITGC_D_Hand1.write('M1' , 'diff x', self.cellfmt_bold  )
        self.ITGC_D_Hand1.write('N1' , 'diff y', self.cellfmt_bold  )
        self.ITGC_D_Hand1.write('O1' , 'diff z', self.cellfmt_bold  )


        self.ITGC_D_Hand1_FT.write('A1' , 'Sr_No' ,self.cellfmt_bold  )
        self.ITGC_D_Hand1_FT.write('B1' , 'SQT processed Image' ,self.cellfmt_bold  )
        self.ITGC_D_Hand1_FT.write('C1' , 'Frame Count',self.cellfmt_bold  )
        self.ITGC_D_Hand1_FT.write('D1' , 'Time stamp',self.cellfmt_bold  )
        self.ITGC_D_Hand1_FT.write('E1' , 'u', self.cellfmt_bold  )
        self.ITGC_D_Hand1_FT.write('F1' , 'v', self.cellfmt_bold  )
        self.ITGC_D_Hand1_FT.write('G1' , 'Expected x', self.cellfmt_bold  )
        self.ITGC_D_Hand1_FT.write('H1' , 'Expected y', self.cellfmt_bold  )
        self.ITGC_D_Hand1_FT.write('I1' , 'Expected z', self.cellfmt_bold  )
        self.ITGC_D_Hand1_FT.write('J1' , 'Actual x', self.cellfmt_bold  )
        self.ITGC_D_Hand1_FT.write('K1' , 'Actual y', self.cellfmt_bold  )
        self.ITGC_D_Hand1_FT.write('L1' , 'Actual z', self.cellfmt_bold  )
        self.ITGC_D_Hand1_FT.write('M1' , 'diff x', self.cellfmt_bold  )
        self.ITGC_D_Hand1_FT.write('N1' , 'diff y', self.cellfmt_bold  )
        self.ITGC_D_Hand1_FT.write('O1' , 'diff z', self.cellfmt_bold  )

        self.ITGC_D_Hand2.write('A1' , 'Sr_No' ,self.cellfmt_bold  )
        self.ITGC_D_Hand2.write('B1' , 'SQT processed Image' ,self.cellfmt_bold  )
        self.ITGC_D_Hand2.write('C1' , 'Frame Count',self.cellfmt_bold  )
        self.ITGC_D_Hand2.write('D1' , 'Time stamp',self.cellfmt_bold  )
        self.ITGC_D_Hand2.write('E1' , 'u', self.cellfmt_bold  )
        self.ITGC_D_Hand2.write('F1' , 'v', self.cellfmt_bold  )
        self.ITGC_D_Hand2.write('G1' , 'Expected x', self.cellfmt_bold  )
        self.ITGC_D_Hand2.write('H1' , 'Expected y', self.cellfmt_bold  )
        self.ITGC_D_Hand2.write('I1' , 'Expected z', self.cellfmt_bold  )
        self.ITGC_D_Hand2.write('J1' , 'Actual x', self.cellfmt_bold  )
        self.ITGC_D_Hand2.write('K1' , 'Actual y', self.cellfmt_bold  )
        self.ITGC_D_Hand2.write('L1' , 'Actual z', self.cellfmt_bold  )
        self.ITGC_D_Hand2.write('M1' , 'diff x', self.cellfmt_bold  )
        self.ITGC_D_Hand2.write('N1' , 'diff y', self.cellfmt_bold  )
        self.ITGC_D_Hand2.write('O1' , 'diff z', self.cellfmt_bold  )

        self.ITGC_D_Hand2_FT.write('A1' , 'Sr_No' ,self.cellfmt_bold  )
        self.ITGC_D_Hand2_FT.write('B1' , 'SQT processed Image' ,self.cellfmt_bold  )
        self.ITGC_D_Hand2_FT.write('C1' , 'Frame Count',self.cellfmt_bold  )
        self.ITGC_D_Hand2_FT.write('D1' , 'Time stamp',self.cellfmt_bold  )
        self.ITGC_D_Hand2_FT.write('E1' , 'u', self.cellfmt_bold  )
        self.ITGC_D_Hand2_FT.write('F1' , 'v', self.cellfmt_bold  )
        self.ITGC_D_Hand2_FT.write('G1' , 'Expected x', self.cellfmt_bold  )
        self.ITGC_D_Hand2_FT.write('H1' , 'Expected y', self.cellfmt_bold  )
        self.ITGC_D_Hand2_FT.write('I1' , 'Expected z', self.cellfmt_bold  )
        self.ITGC_D_Hand2_FT.write('J1' , 'Actual x', self.cellfmt_bold  )
        self.ITGC_D_Hand2_FT.write('K1' , 'Actual y', self.cellfmt_bold  )
        self.ITGC_D_Hand2_FT.write('L1' , 'Actual z', self.cellfmt_bold  )
        self.ITGC_D_Hand2_FT.write('M1' , 'diff x', self.cellfmt_bold  )
        self.ITGC_D_Hand2_FT.write('N1' , 'diff y', self.cellfmt_bold  )
        self.ITGC_D_Hand2_FT.write('O1' , 'diff z', self.cellfmt_bold  )

        self.ITGC_P_Hand1.write('A1' , 'Sr_No' ,self.cellfmt_bold  )
        self.ITGC_P_Hand1.write('B1' , 'SQT processed Image' ,self.cellfmt_bold  )
        self.ITGC_P_Hand1.write('C1' , 'Frame Count',self.cellfmt_bold  )
        self.ITGC_P_Hand1.write('D1' , 'Time stamp',self.cellfmt_bold  )
        self.ITGC_P_Hand1.write('E1' , 'u', self.cellfmt_bold  )
        self.ITGC_P_Hand1.write('F1' , 'v', self.cellfmt_bold  )
        self.ITGC_P_Hand1.write('G1' , 'Expected x', self.cellfmt_bold  )
        self.ITGC_P_Hand1.write('H1' , 'Expected y', self.cellfmt_bold  )
        self.ITGC_P_Hand1.write('I1' , 'Expected z', self.cellfmt_bold  )
        self.ITGC_P_Hand1.write('J1' , 'Actual x', self.cellfmt_bold  )
        self.ITGC_P_Hand1.write('K1' , 'Actual y', self.cellfmt_bold  )
        self.ITGC_P_Hand1.write('L1' , 'Actual z', self.cellfmt_bold  )
        self.ITGC_P_Hand1.write('M1' , 'diff x', self.cellfmt_bold  )
        self.ITGC_P_Hand1.write('N1' , 'diff y', self.cellfmt_bold  )
        self.ITGC_P_Hand1.write('O1' , 'diff z', self.cellfmt_bold  )

        self.ITGC_P_Hand1_FT.write('A1' , 'Sr_No' ,self.cellfmt_bold  )
        self.ITGC_P_Hand1_FT.write('B1' , 'SQT processed Image' ,self.cellfmt_bold  )
        self.ITGC_P_Hand1_FT.write('C1' , 'Frame Count',self.cellfmt_bold  )
        self.ITGC_P_Hand1_FT.write('D1' , 'Time stamp',self.cellfmt_bold  )
        self.ITGC_P_Hand1_FT.write('E1' , 'u', self.cellfmt_bold  )
        self.ITGC_P_Hand1_FT.write('F1' , 'v', self.cellfmt_bold  )
        self.ITGC_P_Hand1_FT.write('G1' , 'Expected x', self.cellfmt_bold  )
        self.ITGC_P_Hand1_FT.write('H1' , 'Expected y', self.cellfmt_bold  )
        self.ITGC_P_Hand1_FT.write('I1' , 'Expected z', self.cellfmt_bold  )
        self.ITGC_P_Hand1_FT.write('J1' , 'Actual x', self.cellfmt_bold  )
        self.ITGC_P_Hand1_FT.write('K1' , 'Actual y', self.cellfmt_bold  )
        self.ITGC_P_Hand1_FT.write('L1' , 'Actual z', self.cellfmt_bold  )
        self.ITGC_P_Hand1_FT.write('M1' , 'Diff x', self.cellfmt_bold  )
        self.ITGC_P_Hand1_FT.write('N1' , 'Diff y', self.cellfmt_bold  )
        self.ITGC_P_Hand1_FT.write('O1' , 'Diff z', self.cellfmt_bold  )

        self.ITGC_P_Hand2.write('A1' , 'Sr_No' ,self.cellfmt_bold  )
        self.ITGC_P_Hand2.write('B1' , 'SQT processed Image' ,self.cellfmt_bold  )
        self.ITGC_P_Hand2.write('C1' , 'Frame Count',self.cellfmt_bold  )
        self.ITGC_P_Hand2.write('D1' , 'Time stamp',self.cellfmt_bold  )
        self.ITGC_P_Hand2.write('E1' , 'u', self.cellfmt_bold  )
        self.ITGC_P_Hand2.write('F1' , 'v', self.cellfmt_bold  )
        self.ITGC_P_Hand2.write('G1' , 'Expected x', self.cellfmt_bold  )
        self.ITGC_P_Hand2.write('H1' , 'Expected y', self.cellfmt_bold  )
        self.ITGC_P_Hand2.write('I1' , 'Expected z', self.cellfmt_bold  )
        self.ITGC_P_Hand2.write('J1' , 'Actual x', self.cellfmt_bold  )
        self.ITGC_P_Hand2.write('K1' , 'Actual y', self.cellfmt_bold  )
        self.ITGC_P_Hand2.write('L1' , 'Actual z', self.cellfmt_bold  )
        self.ITGC_P_Hand2.write('M1' , 'diff x', self.cellfmt_bold  )
        self.ITGC_P_Hand2.write('N1' , 'diff y', self.cellfmt_bold  )
        self.ITGC_P_Hand2.write('O1' , 'diff z', self.cellfmt_bold  )

        self.ITGC_P_Hand2_FT.write('A1' , 'Sr_No' ,self.cellfmt_bold  )
        self.ITGC_P_Hand2_FT.write('B1' , 'SQT processed Image' ,self.cellfmt_bold  )
        self.ITGC_P_Hand2_FT.write('C1' , 'Frame Count',self.cellfmt_bold  )
        self.ITGC_P_Hand2_FT.write('D1' , 'Time stamp',self.cellfmt_bold  )
        self.ITGC_P_Hand2_FT.write('E1' , 'u', self.cellfmt_bold  )
        self.ITGC_P_Hand2_FT.write('F1' , 'v', self.cellfmt_bold  )
        self.ITGC_P_Hand2_FT.write('G1' , 'Expected x', self.cellfmt_bold  )
        self.ITGC_P_Hand2_FT.write('H1' , 'Expected y', self.cellfmt_bold  )
        self.ITGC_P_Hand2_FT.write('I1' , 'Expected z', self.cellfmt_bold  )
        self.ITGC_P_Hand2_FT.write('J1' , 'Actual x', self.cellfmt_bold  )
        self.ITGC_P_Hand2_FT.write('K1' , 'Actual y', self.cellfmt_bold  )
        self.ITGC_P_Hand2_FT.write('L1' , 'Actual z', self.cellfmt_bold  )
        self.ITGC_P_Hand2_FT.write('M1' , 'diff x', self.cellfmt_bold  )
        self.ITGC_P_Hand2_FT.write('N1' , 'diff y', self.cellfmt_bold  )
        self.ITGC_P_Hand2_FT.write('O1' , 'diff z', self.cellfmt_bold  )

        
    
    def add_data(self , ret ) :
        
        if (ret['type'] == "ITGC_D_Hand1") :
            ws = self.ITGC_D_Hand1
            cur_index = self.cur_index_ITGC_D_Hand1
            self.cur_index_ITGC_D_Hand1 = cur_index +1
        elif (ret['type'] == "ITGC_D_Hand1_FT") :
            ws = self.ITGC_D_Hand1_FT
            cur_index = self.cur_index_ITGC_D_Hand1_FT
            self.cur_index_ITGC_D_Hand1_FT = cur_index +1
        elif (ret['type'] == "ITGC_D_Hand2") :
            ws = self.ITGC_D_Hand2
            cur_index = self.cur_index_ITGC_D_Hand2
            self.cur_index_ITGC_D_Hand2 = cur_index +1
        elif (ret['type'] == "ITGC_D_Hand2_FT") :
            ws = self.ITGC_D_Hand2_FT
            cur_index = self.cur_index_ITGC_D_Hand2_FT
            self.cur_index_ITGC_D_Hand2_FT = cur_index +1
        elif (ret['type'] == "ITGC_P_Hand1") :
            ws = self.ITGC_P_Hand1
            cur_index = self.cur_index_ITGC_P_Hand1
            self.cur_index_ITGC_P_Hand1 = cur_index +1
        elif (ret['type'] == "ITGC_P_Hand1_FT") :
            ws = self.ITGC_P_Hand1_FT
            cur_index = self.cur_index_ITGC_P_Hand1_FT
            self.cur_index_ITGC_P_Hand1_FT = cur_index +1
        elif (ret['type'] == "ITGC_P_Hand2") :
            ws = self.ITGC_P_Hand2
            cur_index = self.cur_index_ITGC_P_Hand2
            self.cur_index_ITGC_P_Hand2 = cur_index +1
        elif (ret['type'] == "ITGC_P_Hand2_FT") :
            ws = self.ITGC_P_Hand2_FT
            cur_index = self.cur_index_ITGC_P_Hand2_FT
            self.cur_index_ITGC_P_Hand2_FT = cur_index +1
        else :
            sys.exit(ret['type'])
           
        format = self.cellfmt_normal_left
        ws.write('A'+str(cur_index) , str(cur_index-2) ,self.cellfmt_normal_left )
        ws.write('B'+str(cur_index) , ret['image'], format)
        ws.write('C'+str(cur_index) , ret['Frame Count'] , format)
        ws.write('D'+str(cur_index) , ret['Time'], format)
        ws.write('E'+str(cur_index) , ret['u'], format )
        ws.write('F'+str(cur_index) , ret['v'], format )
        ws.write('G'+str(cur_index) , ret['ex'], self.cellfmt_X_purple )
        ws.write('H'+str(cur_index) , ret['ey'], self.cellfmt_Y_orange )
        ws.write('I'+str(cur_index) , ret['ez'] , self.cellfmt_Z_green )
        if (ws == self.ITGC_D_Hand1 or ws == self.ITGC_D_Hand1_FT) :
            ws.write('J'+str(cur_index) ,  ret['ex'] , self.cellfmt_X_purple )
            ws.write('K'+str(cur_index)  ,  ret['ey'],  self.cellfmt_Y_orange )
            ws.write('L'+str(cur_index) ,    ret['ez'],  self.cellfmt_Z_green )
        else :
            ws.write('J'+str(cur_index) , round(ret['ax'] , 2), self.cellfmt_X_purple )
            ws.write('K'+str(cur_index)  , round (ret['ay'] , 2),  self.cellfmt_Y_orange )
            ws.write('L'+str(cur_index) , round( ret['az'] , 2 ) ,  self.cellfmt_Z_green )
        ws.write_formula('M'+str(cur_index) , '=ABS(G'+str(cur_index)+'-J'+str(cur_index)+')', self.cellfmt_X_purple )
        ws.write_formula('N'+str(cur_index) , '=ABS(H'+str(cur_index)+'-K'+str(cur_index)+')', self.cellfmt_Y_orange )
        ws.write_formula('O'+str(cur_index) , '=ABS(I'+str(cur_index)+'-L'+str(cur_index)+')' , self.cellfmt_Z_green )
        
    
    def close(self ) :
        self.wb.close()
        print("CSV compare report has been made available at " +self.path)
  
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

        infoSheet.write('A7', "Used Callibration File", self.cellfmt_Table2)
        infoSheet.write('B7', self.used_Calibration_file , self.cellfmt_Table2)
        infoSheet.write('C7', "", self.cellfmt_Table2)
        