import zipfile
import re
import concurrent.futures

def read_data(filename):
    total = 0
    with zipfile.ZipFile(filename) as zipfp:
        with zipfp.open(zipfp.namelist()[0],'r') as fp:
            for a_line in fp.readlines():
                a_line = a_line.decode('utf-8')
                for number in re.finditer(r'(\d+(\.?\d*)|\.\d+)',a_line):
                    total += float(number.group())
    return total

files = ['./source/ex2_1.zip', './source/ex2_2.zip', './source/ex2_3.zip', './source/ex2_4.zip', './source/ex2_5.zip']
cnt = 0
with concurrent.futures.ThreadPoolExecutor(max_workers = 5) as executor:
    for i in executor.map(read_data, files):
        cnt += i
print(cnt)
