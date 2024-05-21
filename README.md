# APD-Project-Image-Processing

Utilizând limbajul de programare C++ și mediul de dezvoltare Visual Studio,
proiectul își propune sa permita redimensionarea imaginilor, dar si aplicarea unei
modificari asupra culorilor, obtinandu-se o imagine in nuante de gri si negru.

Folosirea bibliotecii OpenCV si a MPI în proiectul meu de prelucrare a imaginilor a adus
numeroase beneficii. Prin intermediul MPI am putut realiza varianta paralela a codului, avand posibilitatea de a rula pe mai multe procese. Prin intermediul OpenCV, am putut implementa rapid și eficient
operațiuni precum redimensionarea și corectarea culorii, având acces la o gamă largă
de funcții și algoritmi optimizați pentru manipularea eficientă a imaginilor.
Masina pe care am rulat este un PC cu urmatoarele componente:
● Procesorul Intel Core i7-10700F oferă performanțe puternice pentru calcul
intensiv și gaming, cu 8 nuclee și 16 fire, o frecvență de bază de 2.9 GHz și
o frecvență turbo maximă de 4.8 GHz.
● 16 GB RAM
● Placa grafică Radeon RX550 oferă capacități de gaming și de redare a
conținutului media la o rezoluție mai mică, cu 2GB de memorie GDDR5 și
suport pentru tehnologii moderne, cum ar fi DirectX 12 și AMD FreeSync.

![Screenshot 2024-04-02 220722](https://github.com/BiancaVVV/APD-Project-Image-Processing/assets/63341026/b46c0262-3490-4f3e-ae4f-5f05375ed0b0)


![Screenshot 2024-05-07 224546](https://github.com/BiancaVVV/APD-Project-Image-Processing/assets/63341026/dc07481e-f55f-4fb3-a701-146cf8a8a13b)
![Screenshot 2024-05-07 224705](https://github.com/BiancaVVV/APD-Project-Image-Processing/assets/63341026/3d214583-f202-4061-a230-31ce60837ab3)
![Screenshot 2024-05-07 224459](https://github.com/BiancaVVV/APD-Project-Image-Processing/assets/63341026/3c866de7-fd89-4480-866b-7a11bb4a2853)
| 	Image	  | 	MPI	      | 	LIBRARY	 |	Secvential	 | 	Thread     | 
| 	:-----:	| 	:-----:	  | 	:-----:	 | :-----:	     | 	:-----:	   | 
| 	img.jpg	| 	0.0073042	| 	0.269197 |   0.238	     | 	0.015913	 | 
| 	1.jpg 	| 	0.0131903	| 	0.595869 |   0.569	     | 	0.013176	 | 
| 	2.jpg 	| 	0.034950	| 	0.936965 |   0.899	     | 	0.0119501	 | 
| 	3.jpg 	| 	0.016576	| 	0.817354 |   0.859	     | 	0.0104916	 | 
| 	4.jpg 	| 	0.0168793	| 	0.80306	 |   0.793	     | 	0.0229766	 | 
| 	5.jpg	  | 	0.0083154	| 	0.440282 |	 0.439	     | 	0.0110525	 | 
| 	6.jpg   | 	0.0129613 | 	0.703235 |   0.653	     | 	0.0121825	 | 
| 	7.jpeg 	| 	0.0006382	| 	0.0458607|   0.27	       | 	0.0106342	 | 
| 	8.jpg 	| 	0.0148332	| 	0.708411 |   0.690	     | 	0.0125241	 | 
| 	9.jpg 	| 	0.0141461	| 	0.8800009|   0.874	     | 	0.0109062	 | 
| 	10.jpg	| 	0.0619005	| 	1.94384	 |   1.959	     | 	0.0118852	 | 
| 	11.jpg	| 	0.0762553	| 	1.20391	 |   1.160	     | 	0.0114852	 | 
| 	12.jpg	| 	0.0522202	| 	0.875161 |   0.9000	     | 	0.0112653	 | 
