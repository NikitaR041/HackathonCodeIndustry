#include <graphics.h>
#include <string>
#include <iostream>

// ---------- Глобальные параметры ----------
int wx = 800, wy = 600;

// Рисование мигающего курсора
void draw_cursor(int x, int y, int c) {
   setcolor(c);
   line(x, y, x, y + textheight("A") - 1);
}

// Стирание символа
void clear_character(int x, int y) {
   setfillstyle(SOLID_FILL, WHITE);
   bar(x, y, x + textwidth("A") + 5, y + textheight("A"));
}

// Проверка, есть ли символ в допустимой строке
bool allowed_char(char ch, const std::string &allowed) {
   return allowed.find(ch) != std::string::npos;
}

// Ввод строки с мигающим курсором
void entering(int x, int y, std::string &text, int MAX_LENGTH, const std::string &allowed) {
   int cur = 0;
   bool running = true;

   setcolor(BLACK);
   setbkcolor(WHITE);

   while (running) {
      // Мигающий курсор
      draw_cursor(x + textwidth(text.c_str()) + 2, y, cur < 10 ? BLACK : WHITE);
      cur = (cur + 1) % 20;

      if (ismouseclick(WM_LBUTTONDOWN)) {
         clearmouseclick(WM_LBUTTONDOWN);
         running = false;
         continue;
      }

      if (kbhit()) {
         int ch = getch();
         if (ch == 13 || ch == 27) { // Enter или Esc
            running = false;
         }
         else if (ch == 8 && !text.empty()) { // Backspace
            text.pop_back();
            clear_character(x + textwidth(text.c_str()), y);
         }
         else if (allowed_char((char)ch, allowed) && (int)text.size() < MAX_LENGTH - 1) {
            text.push_back((char)ch);
            setcolor(BLACK);
            outtextxy(x, y, text.c_str());
         }
      }
      delay(50);
   }
   draw_cursor(x + textwidth(text.c_str()) + 2, y, WHITE);
}

// ---------- Универсальная кнопка ----------
bool button(int x, int y, int w, int h, const char *label,
            int textOffsetX = 10, int textOffsetY = 5)
{
   setcolor(BLACK);
   rectangle(x, y, x + w, y + h);
   outtextxy(x + textOffsetX, y + textOffsetY, label);

   if (ismouseclick(WM_LBUTTONDOWN)) {
      int mx, my;
      getmouseclick(WM_LBUTTONDOWN, mx, my);
      if (mx > x && mx < x + w && my > y && my < y + h)
         return true;
   }
   return false;
}

// ===================== MAIN =====================
int main() {
   initwindow(wx, wy, "Интерфейс");

   std::string filePath   = "";
   std::string resultName = "untitled.txt";

   // Координаты элементов
   int x1 = 40,  y1 = 60;
   int w1 = 300, h1 = 25;
   int x2 = 40,  y2 = 110;
   int w2 = 300, h2 = 25;
   int xRect = 60, yRect = 220, wRect = 650, hRect = 320;

   int xBtnStart = x1 + w1 + 20, yBtnStart = y1, wBtnStart = 150, hBtnStart = 25;
   int xBtnSave  = x2 + w2 + 20, yBtnSave  = y2, wBtnSave  = 150, hBtnSave  = 25;
   int xBtnDemo  = 200, yBtnDemo = 170, wBtnDemo = 260, hBtnDemo = 30;

   // Отрисовка каркаса один раз
   setbkcolor(WHITE);
   cleardevice();
   setcolor(BLACK);

   outtextxy(x1, y1 - 20, "Введите путь до файла:");
   rectangle(x1, y1, x1 + w1, y1 + h1);

   outtextxy(x2, y2 - 20, "Введите название итогового файла:");
   rectangle(x2, y2, x2 + w2, y2 + h2);

   rectangle(xRect, yRect, xRect + wRect, yRect + hRect);

   // Статические кнопки
   button(xBtnStart, yBtnStart, wBtnStart, hBtnStart, "Старт вычислений");
   button(xBtnSave,  yBtnSave,  wBtnSave,  hBtnSave,  "Сохранить результат");
   button(xBtnDemo,  yBtnDemo,  wBtnDemo,  hBtnDemo,  "Запустить демонстрацию работы");

   // Первичный вывод текста
   outtextxy(x1 + 5, y1 + 5, filePath.c_str());
   outtextxy(x2 + 5, y2 + 5, resultName.c_str());

   while (true) {
      if (ismouseclick(WM_LBUTTONDOWN)) {
         int mx, my;
         getmouseclick(WM_LBUTTONDOWN, mx, my);

         // Поле ввода пути
         if (mx > x1 && mx < x1 + w1 && my > y1 && my < y1 + h1) {
            entering(x1 + 5, y1 + 5, filePath, 255,
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._:/\\");
            clear_character(x1 + 5, y1 + 5);
            outtextxy(x1 + 5, y1 + 5, filePath.c_str());
         }
         // Поле ввода имени
         else if (mx > x2 && mx < x2 + w2 && my > y2 && my < y2 + h2) {
            entering(x2 + 5, y2 + 5, resultName, 255,
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._");
            clear_character(x2 + 5, y2 + 5);
            outtextxy(x2 + 5, y2 + 5, resultName.c_str());
         }
      }

      if (kbhit()) {
         int ch = getch();
         if (ch == 27) break; // ESC – выход
      }
      delay(30);
   }

   closegraph();
   return 0;
}
