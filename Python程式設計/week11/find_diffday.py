import os
from datetime import datetime, timedelta

def list_file_by_time(directory, d):
    today = datetime.today()
    for dirpath, dirnames, filenames in os.walk(directory):
        dir_mtime = datetime.fromtimestamp(os.path.getmtime(dirpath))
        time_diff = today - dir_mtime
        if time_diff <= timedelta(days = d):
            yield dirpath, dir_mtime
        for filename in filenames:
            full_file_name = os.path.join(dirpath, filename)
            file_mtime =  datetime.fromtimestamp(os.path.getmtime(full_file_name))
            time_diff = today - file_mtime
            if time_diff <= timedelta(days=d):
                yield full_file_name, file_mtime
# for f in list_file_by_time("C:\\Users\\Leisurely_Hermit\\Desktop\\LLM", 100):
#     print(f)