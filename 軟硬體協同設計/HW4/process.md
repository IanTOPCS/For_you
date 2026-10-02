1. draw big point 

2. 指定兩點移動
- while 卡住選點
- 求算最邊緣四點(上下左右)

3. 連續移動 (利用指定兩點移動)

---

流程:
1. draw point on LCD (基本題: 亂畫一點)
drawPointOnLCD();

2. draw circle on LCD (點兩下畫圓)
drawHaloCircle();

3. change pen color (增加靈活性，換筆)
changeColor(0);

4. change background color (增加靈活性，換背景)
changeColor(1);

* clear background (單純喜歡黑)
LCD_Clear(0);

5. clear user paint (刷新重畫，為接下來移動畫上合適內容)
clearPaint();

6. draw anything, ex. star, circle etc (方便證明移動)
- colorMode = true (說明即時計算點位顏色)
- press key0 to stop
drawOnLCD();

7. draw anything and move (邊界維護、拖動模式)
- colorMode = false, true (展示彩色模式)
- dragMode = false, true
movePaint(0);
movePaint(1);

8. check all color (螢幕校色)
- imitate real screen function
showAllColor();

9. show user paint on LCD (證明畫被保存)
printGrid();

---

1. uart 加點東西 (malloc 修正錯誤)