from PyPDF2 import PdfFileMerger, PdfFileReader
import os

path = r'E:\Study\SA\YouTubePPT'
files = os.listdir(path)
pdf_files = [f for f in files if f.endswith((".pdf"))]

for files in pdf_files:
    PdfFileMerger.append(PdfFileReader(file(path + files, 'rb')))
if not os.path.exists(path + 'Full Report.pdf'):
    merger.write(path + 'Full Report.pdf')
merger.close()