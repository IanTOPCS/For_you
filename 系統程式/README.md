### Compile assembly code to object code
* 輸出路徑 (可接受多層路徑) : 
    > * 默認路徑 : (source.asm 輸出 source.obj)
    >> ```bash
    >> python ./assembler.py ./source.asm
    >> ```
    > * 指定路徑 : (-o 指定)
    >> ```bash
    >> python ./assembler.py ./source.asm -o ./output.obj
    >> ```

* 編譯模式 : 以 "--sic" 指定當作 SIC 編譯
    > * 指定 SIC 模式 :
    >> ```bash
    >> python ./assembler.py ./source.asm -o ./output.obj --sic
    >> ```
    > * 報錯
    >> 1. \# : immediate addressing mode
    >> 2. @ : indirect addressing mode
    >> 3. BASE : SIC/XE Directive command
    >> 4. SIC/XE : command of SIC/XE
    
    > * 檢查 :
    >> * SIC address range (rg) (0 &le; rg &le; $(2^{15}-1)$)

### Compare file (checkObjectCode.py)
* 容錯 : 忽略檔案最後一行的「行尾換行」
    >> ```bash
    >>  python ./checkObjectCode.py ./source.obj ./target.obj
    >> ```

### 物件檔格式
* T-record 非 60 字元塞滿才換行 :
    > [(此行指令) + (累積當行指令)]>60 才換行

### 正常測試 (老師指定檔案) :
* 保證檔案 (asm) 於指定模式 (Mode) 編譯，與目標檔案 (obj) 相同

|Source (asm)|Mode|Target (obj)|
|-|-|-|
|textbooksicxe|SIC/XE|textbooksicxe(textbook).obj|
|addexample|SIC|addexample|
|studentexample|SIC|studentexample|
|textbookexample|SIC|textbookexample|

### 壓力測資 (strange.asm) :
> * 測試內容 :
>> 1. 重複 START
>> 2. START 地址 (值域、空白容許)
>> 3. 行中註解
>> 4. indirect label (存在、空白容許)
>> 5. 立即值 (正負、值域)
>> 6. 暫存器 (個數、大小寫容許、空白容許、行尾逗號容許)
>> 7. format-4 JSUB (強迫 BASE 設定)
>> 8. BYTE 格式 (hex 值域、char 大小寫與空白保留、空白容許)
>> 9. Reserve byte/word 值域
>> 10. 記憶體檢查 (上限 1M)

### 流程
* (myTable)
1. 考慮指令 format 1~3
    > * 有 4 者必有 3 ，無需特別考慮4 (需 programmer 使用"+"指定 4 )

    > * 區分 SIC 與 SIC/XE 指令

* (fileChecker.py)
2. 模仿終端參數指令 (from python module "argparse")
    > * 接受多層路徑
    
    > * 檢查 :
    >> 1. 來源檔路徑檢查
    >> 2. 輸出後綴(.obj)檢查

* (breakLines.py)
3. 指令拆解 :
    > * 註解行排除 :
    >> 1. 行中註解
    >> 2. 整行註解

    > * 錯誤檢查 :
    >> 1. hex 數字檢查
    >> 2. 字串封閉檢查 (兩個')
    >> 3. \# 與 @ 空白排除 (指令長度2時)

    > * 特別解釋: 指令長度3時，考 operand 為 char，不可合併空白

4. 將分解指另依 Object (Line) 包裝
    > * 含每個指令長度下 error 檢查

* (passerOne.py)
5. 建立 Symbol table、總記憶體計算 :
    > * START 檢查 :
    >> 1. 第一行必為 START
    >> 2. 重複 START
    >> 3. 排除空格地址是否合法 (十進治)

    > * RESB/RESW 檢查 :
    >> 1. displacement 15-bits range (rg) (0 &le; rg &le; $(2^{15}-1)$)
    >> 2. 負數阻擋 (採十進治，可接受含"+"符號、空白)

    > * 雜項檢查 :
    >> * label 重複檢查
    >> * 總記憶體 1M
    >> * 非 opcode/directive 指令

    > * 特別解釋: 已於 breakLine 做表示 hex X'、char C'字母大寫，無需考慮此時大小寫問題

* (passerTwo.py)
6. 計算 records :
    > * 所有指令格式具 SIC 模式下對 SIC/XE 指令錯誤偵測

    > * 指令格式 2 檢查 :
    >> 1. 暫存器過多
    >> 2. 指定暫存器不存在
    >> 3. 未指定暫存器

    > * 指令格式 3 :
    >> * 特例 "RSUB": (沒有 operand) 
    >>> 1. SIC :
    >>>> * (8 bits op) + (X) + (15 bits displacement) => 4C0000
    >>> 2. SIC/XE :
    >>>> * (6 bits op | 0x03) + (e=0) + (15 bits displacement) => 4F0000

    >> * 兼容 SIC 檢查 :
    >>> 1. Out of pc-relative
    >>> 2. Out of base-relative
    >>> 3. Opcode $\in$ SIC
    >>> $\newline$ => 嘗試以 SIC 方式組合
    
    >> * 檢查 :
    >>> 1. Operand lost (未指定)
    >>> 2. Register X (可接受空格、行尾逗號", X,")
    >>> 3. Immediate value (iv) range ($-2^{11}$ &le; iv &le; $(2^{11}-1)$)
    >>> 4. PC-relative (pc) range ($-2^{11}$ &le; pc &le; $(2^{11}-1)$)
    >>> 5. Base-relative (b) range (0 &le; b &le; $(2^{12}-1)$)
    >>> 6. SIC address range (rg) (0 &le; rg &le; $(2^{15}-1)$)
    >>> 7. Opcode/Directive isn't exist

    > * 指令格式 4 :
    >> * 特例 "RSUB": (沒有 operand)
    >>>> * (6 bits op | 0x03) + (e=1) + (20 bits displacement) => 4F10000

    >> * 檢查 :
    >>> * Immediate value (iv) range ($-2^{19}$ &le; iv &le; $(2^{19}-1)$)

    > * Directive 檢查:
    >> 1. WORD 檢查 :
    >>> 1. 合法數字 (可含正負號、空白)
    >>> 2. WORD range (wr) range ($-2^{23}$ &le; wr &le; $(2^{23}-1)$)

    >> 2. Label error (沒有 label)

    > * 忽略重複 END 錯誤
    

* (fileChecker.py)
7. 生成 .obj 檔 :
    > * 檢查 :
    >> 1. 資料夾 (自動創立)
    >> 2. 權限檢查 (permission deny)

* (assembler.py)
8. 確認結果 :
    > * 成功 :
    >> ```bash
    >> Please check output file output.obj.
    >>```
    > * 失敗 :
    >> ```bash
    >> Error: error message
    >>```