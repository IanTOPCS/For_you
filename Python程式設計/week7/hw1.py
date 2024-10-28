import sys

for i, aline in enumerate(sys.stdin.readlines()):

    errors=[]
    fields = aline.strip().split(',')
    line_no= i+1
    field_no= len(fields)
    try:
        if field_no < 4:
            raise Exception(f'資料欄位數不足: line:{line_no} 欄位數:{field_no}')
        if field_no > 4:
            raise Exception(f'資料欄位數過多: line:{line_no} 欄位數:{field_no}')
        format_errors=[]
        value_errors=[]

        try:
            int(fields[1])
        except ValueError:
            if(fields[1].isdigit()):
                value_errors.append(2)
            else:
                format_errors.append(2)

        try:
            int(fields[2])
        except ValueError:
            if(fields[2].isdigit()):
                value_errors.append(3)
            else:
                format_errors.append(3)

        if(fields[3] not in ['0', '1']):
            if(fields[3].isdigit()):
                value_errors.append(4)
            else:
                format_errors.append(4)

        if format_errors or value_errors:
            error_message=''
            if format_errors and value_errors:
                error_message += f"資料格式錯誤與值錯誤: "
            elif format_errors:
                error_message += f"資料格式錯誤: "
            elif value_errors:
                error_message += f'資料值錯誤: '
            error_message += f"line:{line_no}"
            if format_errors:
                error_message += f" 格式錯誤:{','.join(map(str, format_errors))}"
            if value_errors:
                error_message += f" 值錯誤:{','.join(map(str, value_errors))}"
            errors.append(error_message)
    except Exception as e:
        print(e)
    for error in errors:
        print(error)