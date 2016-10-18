#include<gtk/gtk.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>



int main(int argc, char *argv[])
{
if (argc==1)
{
goto loop;
}

if(strcmp(argv[1], "-h") == 0){

printf("usage: gcc menu2.c `pkg-config --libs gtk+-2.0` `pkg-config --cflags gtk+-2.0` or make and then ./try");

return 0;
}

loop:

gtk_init(&argc,&argv); //initialize gtk
GtkWidget *window, *button, *vbox, *menu_bar, *game_menu, *help_menu; //declare widgets variables
GtkWidget *newgameMi;
GtkWidget *setMi;
GtkWidget *highMi;
GtkWidget *exitMi;
GtkWidget *aboutMi;
GtkWidget *howMi;
GtkWidget *GAME_MENU;
GtkWidget *SET_GAME;
GtkWidget *easy;
GtkWidget *medium;
GtkWidget *hard;
GtkWidget *sep;

window=gtk_window_new(GTK_WINDOW_TOPLEVEL);  //create window
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 200); //size of the window
  gtk_window_set_title(GTK_WINDOW(window), "Sudoku");
g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);  //event when the window is closed using x

menu_bar=gtk_menu_bar_new(); 

 
GAME_MENU=gtk_menu_new();
game_menu=gtk_menu_item_new_with_label("Game"); 
                    


SET_GAME=gtk_menu_new();
setMi=gtk_menu_item_new_with_label("Set Game Difficulty");  
easy=gtk_menu_item_new_with_label("easy"); 
medium=gtk_menu_item_new_with_label("medium");
hard=gtk_menu_item_new_with_label("hard");  

gtk_menu_item_set_submenu(GTK_MENU_ITEM(setMi),SET_GAME);
gtk_menu_shell_append(GTK_MENU_SHELL(SET_GAME),easy);
gtk_menu_shell_append(GTK_MENU_SHELL(SET_GAME),medium);
gtk_menu_shell_append(GTK_MENU_SHELL(SET_GAME),hard);
sep=gtk_separator_menu_item_new();

newgameMi=gtk_menu_item_new_with_label("New Game");
highMi=gtk_menu_item_new_with_label("High Scores");
exitMi=gtk_menu_item_new_with_label("Exit");
 



  
gtk_menu_item_set_submenu(GTK_MENU_ITEM(game_menu),GAME_MENU);
gtk_menu_shell_append(GTK_MENU_SHELL(GAME_MENU),setMi);
//gtk_menu_shell_append(GTK_MENU_SHELL(GAME_MENU),sep);
//gtk_menu_shell_append(GTK_MENU_SHELL(GAME_MENU),newgameMi);
//gtk_menu_shell_append(GTK_MENU_SHELL(GAME_MENU),sep);
//gtk_menu_shell_append(GTK_MENU_SHELL(GAME_MENU),highMi);
gtk_menu_shell_append(GTK_MENU_SHELL(GAME_MENU),sep);
gtk_menu_shell_append(GTK_MENU_SHELL(GAME_MENU),exitMi);
gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),game_menu);

g_signal_connect(G_OBJECT(exitMi), "activate",G_CALLBACK(gtk_main_quit), NULL);

//help_menu=gtk_menu_item_new_with_label("Help");                   
//gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item),help_menu);
//gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),menu_item);


//aboutMi=gtk_menu_item_new_with_label("About");             
//gtk_menu_shell_append(GTK_MENU_SHELL(help_menu),menu_item);

//howMi=gtk_menu_item_new_with_label("How To Play");             
//gtk_menu_shell_append(GTK_MENU_SHELL(help_menu),menu_item);

vbox=gtk_vbox_new(0,0);                                      
gtk_box_pack_start(GTK_BOX(vbox),menu_bar,0,0,0);

gtk_container_add(GTK_CONTAINER(window),vbox);
gtk_widget_show_all(window);

gtk_main();

return 0;
}
//help_menu=gtk_menu_new();

