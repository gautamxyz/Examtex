#Examtex
# Instructions on compilation

* First the question bank is created(here we have already created questionbank.txt). For the purpose of this project the question bank contains MCQs and Fill in the blanks questions. All questions have difficulty level from 0 (easiest) to 1 (hardest).
  
* Then a question paper file is to be created (here we have created qp.txt) which contains instructions regarding the following-:
  * Which type(s) of questions do you want in the question papers.
  * The upper and lower bounds of difficulties of questions that you want in your question papers.
  * Number of questions of each type that you want in question papers. The syntax for this is as given in qp.txt
  
*  On terminal run "gcc ast.h ast.c Main.c". Then run ./a.out
*  If any of the following happen then an "ERROR!" message will get printed in the 3 question paper files and a message will get flashed on the terminal describing the nature of error-:
   * If the user asks for more questions belonging to the difficulty range (specifed by him/her in qp.txt), than the number of such questions available in the question bank
   * if the upper bound of difficulty level requested is > 0.9 or lower bound of difficulty is < 0.1
   * if upper bound of difficulty level, for a particular type of question, specified in qp.txt is greater than lower bound of difficulty level for that type of question
   * if there is a syntax error in either qp.txt or questionbank.txt
  
  **Note**- There must not be any blank lines in the qp.txt file and questionbank.txt file otherwise it will throw a syntax error.
*  If all the above errors are avoided in questionbank.txt and qp.txt then 3 question papers will be generated in .md format
*  To obtain PDFs run the command "pandoc -s -o paper1.pdf questionpaper1.md" on your terminal.
*  This will generate pdf of paper1. Similarly pdfs of paper 2 & 3 can be generated.


# Marks File

* Suppose the current difficulty of a certain question is d where 0<=d<=1.
* We assume that we are given what fraction of students who attempted that question could not get it right(say x).
* We upgdate d to x. This we do for every question that appeared in the question papers.
* For example a question has a difficulty level of 0.4. And we are given that 0.2 fraction of students could not get that question right. So new difficulty = 0.2 
