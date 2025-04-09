# pie-at-home
"lackluster"

A volunteer computing project where multiple clients can contribute into the calcuation of pi (Our goal is 400 trillion digits)  

This program will use variants Bailey–Borwein–Plouffe formula (or BBP) since it has the ability to  
calcuate any digit of pi without having to calcuate the preceding digits, this ability is what  
will enable us to distribute the computation tasks across devices.  

This program was inspired by Great Internet Mersenne Prime Search (GIMPS), SETI@home and Minecraft@home.  


This will consist of two parts:
The client side: calculates Pi using algorithm in number ranges (0-1000, 1001-2000 and so) and communicates with the server for "tasks"   
(which are just the number ranges of pi the computer has to calcuate) that are dynamically adjusted according to the computer's specs.  

The server side: gives out tasks that are calcuated and the result of those tasks are pieced by the server and put in a file, I believe the only big  
thing the server would really require is storage for the digits, but maybe if enough people download it, the server might get a decent load, maybe even overload.  

This however poses a problem, which being, the verification of the digits recieved, bad actors could try to change the correct digits to incorrect ones,  
OR the computer may compute incorrect digits. (This problem will currently be ignored until the server is finished.)
