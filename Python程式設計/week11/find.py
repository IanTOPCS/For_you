import os

def list_file_by_size(directory, n):
    for dirpath, dirnames, filenames in os.walk(directory):
        for filename in filenames:
            full_file_name = os.path.join(dirpath, filename)
            filesize = os.path.getsize(full_file_name)
            if filesize >= n:
                yield(full_file_name, filesize)
                
# for f in list_file_by_size("C:\\Users\\Leisurely_Hermit\\Desktop\\ImageDeal\\python", 100):
#     print(f)