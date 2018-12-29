# plsucks
Calculeaza codificarea starilor din organigrama

Intra pe https://csacademy.com/app/graph_editor/ si construieste graful asociat organigramei tale, in care un nod reprezinta o stare si exista o muchie intre doua noduri daca starile lor asociate sunt legate, adica se poate ajunge dintr-una in cealalta. In fisierul in.in pune pe prima linie numarul de noduri (Node Count) si pe urmatoarele linii copiaza ce e la Graph Data (pe primele n linii sunt denumirile nodurilor, iar dupa sunt puse muchiile). Merge cu maxim 16 noduri. Fisierul dat deja e un exemplu.

Programul e facut in CodeBlocks si probabil ca merge compilat si altfel. Daca din orice motiv nu merge importat proiectul, poti sa faci si un proiect nou in C++, sa copiezi ce e in main.cpp, sa creezi fisierul in.in in acelasi folder si sa adaugi la project->build options -std=c++11.

Cand rulezi, e afisat in consola hazardul minim, adica produsul dintre toate diferentele de biti ale codificarilor nodurilor adiacente. Dupa e afisat fiecare nod cu codificarea lui in bazele 2 si 10. E posibil sa ruleze pentru destul de mult timp in unele cazuri (mai ales la grafuri cu multe muchii). Daca da eroare, te rog sa verifici datele de intrare ca programul presupune ca sunt corecte.

Inca nu e testat prea bine, deci e posibil sa crape sau sa nu dea bine, caz in care te rog sa ma anunti :)
