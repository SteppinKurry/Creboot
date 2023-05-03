# Creboot
A program that encrypts text files. Pretty cool

Like I said above, this is a program that "encrypts" text files. I'm not sure if it's actually encryption or not, but who cares? I think it's cool.

qmenu.c has been added as the menu. It doesn't allow switching keys/charts files on the fly, but, as the name suggests, it's a very quick menu 
(one command and two arguments). This is the current suggested way to get the full Creboot experience. As always, creboot.c and creboot.h work 
fine on their own, so if you want to include them in your own project, be my guest. Maybe you can make an actually good menu with them.

In order for an encryption/decryption to successfully occur, you need three things:
1. Message/text file
2. Key
3. Charts file

The first two are pretty self-explanatory, but the third one is a little unusual. Don't ask me why I decided to call it a charts file; it's a long story. 
The charts file is essentially a text file containing all possible keystrokes on the keyboard (0-9, a-z, etc.). I'm not interested in getting into the 
specifics right now, so if you plan to use this program, I reccomend that you use one of the ones I included; they're good to go. Bad charts files are 
a great way to obliterate your files in an unrecoverable manner. 

If you decrypt a file with a different charts file, it will not work properly. For a file to be properly encrypted, you need the correct key and charts 
file.

Also, encryption and decryption are just opposites of each other. This leads to interesting situations where you could initially "decrypt" a file, and the 
person on the other end would have to know to "encrypt" it to get the message out. You could also encrypt mulitple times in a row, potentially using 
different charts files for each one.

I think that's enough explanation from me for now. If for some reason you have any interest in using this, I wish you luck, and I hope you enjoy 
the little program I made. It's been fun to work on.
