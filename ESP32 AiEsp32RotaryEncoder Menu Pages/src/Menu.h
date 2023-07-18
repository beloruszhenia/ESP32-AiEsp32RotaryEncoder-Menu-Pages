#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


class Menu {
  private:
    String *options;  // array of menu options
    int num_options;  // number of menu options
    int selected;     // currently selected option
    int page;         // current page of options
    int max_pages;    // maximum number of pages
    int items_per_page; // number of items per page
    int top_item;     // index of top item on page
    int x_pos;        // x position of menu on display
    int y_pos;        // y position of menu on display
    int font_size;    // font size for menu options
    int menuOptionSellected;

  public:
    Menu(String *opts, int num_opts, int xpos, int ypos, int font_size) {
      options = opts;
      num_options = num_opts;
      selected = 0;
      page = 1;
      max_pages = ceil(num_options / 3.0);
      items_per_page = 3;
      top_item = 0;
      x_pos = xpos;
      y_pos = ypos;
      this->font_size = font_size;
      menuOptionSellected = 0;
    }


    void drawMainMenu(
      display.clearDisplay();
      display.setTextSize(font_size);
      display.setCursor(x_pos, y_pos);
      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      display.println("Select an option:");
      for (int i = top_item; i < top_item + items_per_page; i++) {
        if (i >= num_options) {
          break;
        }
        if (i == selected) {
          display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
        } else {
          display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        }
        display.setCursor(x_pos, y_pos + (i - top_item + 1) * font_size * 8);
        display.println(options[i]);
      }
      display.display();
    )

    drawMenuOption(){

    };

    void drawMenu() {
      if (menuOptionSellected)
          drawMainMenu();
        else
          drawMenuOption();
    }

    void nextPage() {
      if (page < max_pages) {
        page++;
        top_item += items_per_page;
        selected = top_item;
        drawMenu();
      }
    }

    void prevPage() {
      if (page > 1) {
        page--;
        top_item -= items_per_page;
        selected = top_item + 2;        
        drawMenu();
      }
    }

    int getSelected() {
      return selected;
    }

    void setSelected(int index) {
      selected = index;
      drawMenu();
    }

    void scroll(int direction ){
        if (direction > 0 && selected < num_options - 1) {
             selected++;
            if (selected >= top_item + items_per_page) {
                nextPage();
            } else {
                drawMenu();
            }
        } else if (direction < 0 && selected > 0) {
            selected--;
            if (selected < top_item) {
                 prevPage();
            } else {
                 drawMenu();
            }
        }

    }

    void selectButton(){
        if (menuOptionSellected == 0)
          menuOptionSellected = 1;
        else
          menuOptionSellected = 0;
        
        // display.clearDisplay();
        // display.setTextSize(1);
        // display.setCursor(0, 0);
        // display.println("Selected:");
        // display.setCursor(0, 16);
        // display.print(options[selected]);
        // display.print(": ");
        // display.println(num_options);
        // display.display();
        // delay(1500);
        
        // drawMenu(); 
    }
};
