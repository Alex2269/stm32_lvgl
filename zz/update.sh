#!/bin/sh

   #******************************************
   # echo "# stm32_lvgl" >> README.md
   rm -rf .git
   git init
   git status
   git add .
   git commit -m "$(date "+%Y-%m-%d")"
   git branch -M master
   git remote add origin git@github.com:Alex2269/stm32_lvgl.git
   git push -u origin master
   git pull
   #******************************************

   #******************************************
   видалення останніх комітів:
   # git reset HEAD^    --hard
   #
   git reset  origin    --hard
   git reset  HEAD~1    --hard
   git reset  HEAD~1    --hard
   git reset  HEAD~1    --hard
   git push origin HEAD --force
   #******************************************

   #******************************************
   оновлення та полсилання файлів на сховищє:
   #
   git status
   git add .
   git commit -m "$(date "+%Y-%m-%d")"
   git push -u origin master
   git pull
   #******************************************

