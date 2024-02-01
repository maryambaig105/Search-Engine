#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include "BSTsearchTree.h"
#include "Hashtable.h"
#include "strutils.h"
#include "sorting.h"

using namespace std;

//returns the index of file in files otherwise -1
int inWordItem(string &file,vector<DocumentItem> files){
    int s=files.size();
    for(int i=0;i<s;i++){
        if(files[i].documentName==file){
            return i;
        }
    }
    return -1;
}
//checks if all words are in that documents
bool inDoc(vector<vector<DocumentItem>> allwords, string &file){
    for (int j = 0; j < allwords.size(); j++) {
        bool found = false;
        for (int k = 0; k < allwords[j].size(); k++) {
            if (allwords[j][k].documentName == file) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}
void QueryTree(vector<string> storefiles, vector<string> storewords, BSTsearchTree<string,WordItem>& tree){
    bool nodoc=false;
    vector<vector<DocumentItem>> storeall;
    for(int i=0;i<storewords.size();i++){
        //create a vector for each word
        vector<DocumentItem> x;
        string word1=storewords[i];
        ToLower(word1);
        if(tree.find(word1)){
            //find size of that words wordItem
            //vector<DocumentItem> temp;
            //temp=tree.wItem(word)->documents;
            int s =tree.wItem(word1)->documents.size();
            for(int j=0;j<s;j++){
                DocumentItem temp;
                temp.count=tree.wItem(word1)->documents[j].count;
                temp.documentName=tree.wItem(word1)->documents[j].documentName;
                //store each doc and count to print
                x.push_back(temp);
            }
            storeall.push_back(x);
        }

        else{
            //that word does not exist in the tree so need to display no document
            //cout<<"No document contains the given query"<<endl;
            nodoc=true;
        }


    }

    if(nodoc){
    }
    else{
        for(int i=0;i<storefiles.size();i++){
            //we need to check if all words in query are in that document to print if not dont print that document
            if(inDoc(storeall,storefiles[i])){
            }

        }
    }

}

void QueryTable(vector<string> storefiles, vector<string> storewords, HashTable<string,WordItem>& table){
    bool nodoc=false;
    vector<vector<DocumentItem>> storeall;
    for(int i=0;i<storewords.size();i++){
        //create a vector for each word
        vector<DocumentItem> x;
        string word1=storewords[i];
        ToLower(word1);
        if(table.find(word1)){
            //find size of that words wordItem
            //vector<DocumentItem> temp;
            //temp=tree.wItem(word)->documents;
            int s =table.getItem(word1)->documents.size();
            for(int j=0;j<s;j++){
                DocumentItem temp;
                temp.count=table.getItem(word1)->documents[j].count;
                temp.documentName=table.getItem(word1)->documents[j].documentName;
                //store each doc and count to print
                x.push_back(temp);
            }
            storeall.push_back(x);
        }

        else{
            nodoc=true;
        }
    }

    if(nodoc){
    }
    else{
        for(int i=0;i<storefiles.size();i++){
            //we need to check if all words in query are in that document to print if not dont print that document
            if(inDoc(storeall,storefiles[i])){
            }
        }
    }

}


int binarySearch(const vector<WordItem>& sortedArray, string word) {
    int left = 0;
    int right = static_cast<int>(sortedArray.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (sortedArray[mid].word == word) {
            return mid;  // Found the target
        } else if (sortedArray[mid].word < word) {
            left = mid + 1;  // Search in the right half
        } else {
            right = mid - 1;  // Search in the left half
        }
    }

    return -1;  // Target not found
}

void Binary(vector<string> storefiles, vector<string> storewords, vector<WordItem>& sortedArray){
    bool nodoc=false;
    vector<vector<DocumentItem>> storeall;
    for(int i=0;i<storewords.size();i++){
        //create a vector for each word
        vector<DocumentItem> x;
        string word1=storewords[i];
        ToLower(word1);
        int indexvector=binarySearch(sortedArray,word1);
        if(indexvector!=-1){
            int s =sortedArray[indexvector].documents.size();
            for(int j=0;j<s;j++){
                DocumentItem temp1;
                temp1.count=sortedArray[indexvector].documents[j].count;
                temp1.documentName=sortedArray[indexvector].documents[j].documentName;
                x.push_back(temp1);
            }
            storeall.push_back(x);
        }
        else{
            nodoc=true;
        }
    }

    if(nodoc){
    }
    else{
        for(int i=0;i<storefiles.size();i++){
            //we need to check if all words in query are in that document to print if not dont print that document
            if(inDoc(storeall,storefiles[i])){
            }
        }
    }

}

int main() {

    int Docs=0,element=0;//get number of documents
    cout<<"Enter number of input files: ";
    cin>>Docs;

    string filename,line;//get filenames and save them in an array ,storefiles[Docs]
    vector<string> storefiles;
    //initialize tree with dummy node
    WordItem * temp=NULL;
    BSTsearchTree<string ,WordItem> tree(" ",temp) ;
    HashTable<string,WordItem> Htable(53);
    vector<WordItem> initial,sortvec1,sortvec2,sortvec3,sortvec4,sortvec5,sortvec6;
    for(int i=0;i<Docs;i++){
        cout<<"Enter "+to_string(i+1)+". file name: ";
        cin>>filename;
        storefiles.push_back(filename);
    }
    //process data from files
    vector<string> allwords;
    for(int i=0;i<Docs;i++){
        string h=storefiles[i];
        ifstream file(h);
        if (file.is_open()){
            string word;

            while(file >> word){
                // Convert word to lowercase and remove punctuation
                ToLower(word);
                //use strip to remove punctuation
                StripPunc(word);
                //remove white space
                StripWhite(word);
                //remove numbers
                bool number=false;
                int counter=0;
                for(int i=0;i<word.length();i++){
                    if(isdigit(word[i])){
                        counter++;
                    }
                }
                if(counter!=word.length()){
                    istringstream iss(word);
                    string token;
                    while (getline(iss, token)) {
                        // Split the token based on the set of delimiters
                        size_t start = 0;
                        size_t pos;
                        while ((pos = token.find_first_not_of("abcdefghijklmnopqrstuvwxyz", start)) != std::string::npos) {
                            if (pos > start) {
                                allwords.push_back(token.substr(start, pos - start));
                            }
                            start = pos + 1;
                        }
                        if (start < token.length()) {
                            allwords.push_back(token.substr(start));
                        }
                    }
                }



            }
        }

        file.close();
        string document=storefiles[i];

        for(int y=0;y<allwords.size();y++) {

            if (tree.find(allwords[y])) {
                //check if that document exists in its worditem if yes increase count, if not add document with count 1
                vector<DocumentItem> Ntemp = tree.wItem(allwords[y])->documents;
                if (inWordItem(document, Ntemp) >= 0) {
                    //check if document name is the same as the doc we are reading then increase count
                    int index = inWordItem(document, Ntemp);
                    if (index == -1) {
                        //that means document is not in the vector, so add it
                        DocumentItem Atemp;
                        Atemp.count = 1;
                        Atemp.documentName = document;
                        //tree.wItem(word)->word=word;
                        tree.wItem(allwords[y])->documents.push_back(Atemp);
                    } else {
                        tree.wItem(allwords[y])->documents[index].count++;
                    }

                } else {
                    DocumentItem Atemp;
                    Atemp.count = 1;
                    Atemp.documentName = document;
                    //tree.wItem(word)->word=word;
                    tree.wItem(allwords[y])->documents.push_back(Atemp);
                }
            } else {
                //if word not in tree insert node
                WordItem *worditem = new WordItem();
                DocumentItem Btemp;
                Btemp.count = 1;
                Btemp.documentName = document;
                worditem->documents.push_back(Btemp);
                worditem->word = allwords[y];
                tree.insert(allwords[y], worditem);

            }

        }
        for(int z=0;z<allwords.size();z++){

            if (Htable.find(allwords[z])) {
                //check if that document exists in its worditem if yes increase count, if not add document with count 1
                vector<DocumentItem> Ntemp = Htable.getItem(allwords[z])->documents;
                if (inWordItem(document, Ntemp) >= 0) {
                    //check if document name is the same as the doc we are reading then increase count
                    int index = inWordItem(document, Ntemp);
                    if (index == -1) {
                        //that means document is not in the vector, so add it
                        DocumentItem Atemp;
                        Atemp.count = 1;
                        Atemp.documentName = document;
                        //tree.wItem(word)->word=word;
                        Htable.getItem(allwords[z])->documents.push_back(Atemp);
                    } else {
                        Htable.getItem(allwords[z])->documents[index].count++;
                    }

                } else {
                    DocumentItem Atemp;
                    Atemp.count = 1;
                    Atemp.documentName = document;
                    //tree.wItem(word)->word=word;
                    Htable.getItem(allwords[z])->documents.push_back(Atemp);
                }
            } else {
                //if word not in tree insert node
                WordItem *worditem = new WordItem();
                DocumentItem Btemp;
                Btemp.count = 1;
                Btemp.documentName = document;
                worditem->documents.push_back(Btemp);
                worditem->word = allwords[z];
                Htable.insert(allwords[z], worditem);

            }

        }

        for(int b=0;b<allwords.size();b++){
            //find if word is in the vector already
            bool found=false,doc=false;
            int index=0;
            for(int l=0;l<sortvec1.size();l++){
                if(sortvec1[l].word==allwords[b]){
                    index=l;
                    found=true;
                }
            }

            if(found==true){
                //check if document is in the worditem vector
                WordItem temp=sortvec1[index];
                for(int g=0;g<temp.documents.size();g++){
                    if(temp.documents[g].documentName==document){
                        initial[index].documents[g].count++;
                        sortvec1[index].documents[g].count++;
                        sortvec2[index].documents[g].count++;
                        sortvec3[index].documents[g].count++;
                        sortvec4[index].documents[g].count++;
                        sortvec5[index].documents[g].count++;
                        sortvec6[index].documents[g].count++;
                        doc=true;
                        break;
                    }
                }

                if(doc==false){
                    DocumentItem Atemp;
                    Atemp.count = 1;
                    Atemp.documentName = document;
                    initial[index].documents.push_back(Atemp);
                    sortvec1[index].documents.push_back(Atemp);
                    sortvec2[index].documents.push_back(Atemp);
                    sortvec3[index].documents.push_back(Atemp);
                    sortvec4[index].documents.push_back(Atemp);
                    sortvec5[index].documents.push_back(Atemp);
                    sortvec6[index].documents.push_back(Atemp);
                }
            }
            else{
                WordItem worditem ;
                DocumentItem Btemp;
                Btemp.count = 1;
                Btemp.documentName = document;
                worditem.documents.push_back(Btemp);
                worditem.word = allwords[b];
                initial.push_back(worditem);
                sortvec1.push_back(worditem);
                sortvec2.push_back(worditem);
                sortvec3.push_back(worditem);
                sortvec4.push_back(worditem);
                sortvec5.push_back(worditem);
                sortvec6.push_back(worditem);

            }
        }
        allwords.clear();
    }

    ///remove the dummy node i created to start the tree.
    WordItem * x= tree.wItem(" ");
    tree.remove(" ",x);
    //after pre processing
    Htable.after();
    //sort initial vector
    initial=insertionSort2(initial);

    cin.ignore();
    cout<<endl<<"Enter queried words in one line: ";
    getline(cin,line);
    ToLower(line);

    vector<string> storewords;
    //read line word for word and search for the words
    string word;
    stringstream query(line);
    bool nodoc=false,nodoc1=false,nodoc2=false;
    while(query>>word){
        //store words in a vector
        ToLower(word);
        istringstream iss(word);
        string token;
        while (getline(iss, token)) {
            // Split the token based on the set of delimiters
            size_t start = 0;
            size_t pos;
            while ((pos = token.find_first_not_of("abcdefghijklmnopqrstuvwxyz", start)) != std::string::npos) {
                if (pos > start) {
                    storewords.push_back(token.substr(start, pos - start));
                }
                start = pos + 1;
            }
            if (start < token.length()) {
                storewords.push_back(token.substr(start));
            }
        }
    }

    vector<vector<DocumentItem>> storealltree;
    vector<vector<DocumentItem>> storealltable;
    vector<vector<DocumentItem>> storeallvector;

    for(int i=0;i<storewords.size();i++){
        //create a vector for each word
        vector<DocumentItem> x1;
        string word1=storewords[i];
        ToLower(word1);
        if(tree.find(word1)){
            //find size of that words wordItem
            //vector<DocumentItem> temp;
            //temp=tree.wItem(word)->documents;
            int s =tree.wItem(word1)->documents.size();
            for(int j=0;j<s;j++){
                DocumentItem temp1;
                temp1.count=tree.wItem(word1)->documents[j].count;
                //cout<<tree.wItem(word1)->documents[j].count<<endl;
                temp1.documentName=tree.wItem(word1)->documents[j].documentName;
                //cout<<tree.wItem(word1)->documents[j].documentName<<endl;
                //store each doc and count to print
                x1.push_back(temp1);
            }
            storealltree.push_back(x1);
        }

        else{
            //that word does not exist in the tree so need to display no document
            //cout<<"No document contains the given query"<<endl;
            nodoc=true;
        }
        if(Htable.find(word1)){
            //find size of that words wordItem
            //vector<DocumentItem> temp;
            //temp=tree.wItem(word)->documents;
            int s =Htable.getItem(word1)->documents.size();
            for(int j=0;j<s;j++){
                DocumentItem temp1;
                temp1.count=Htable.getItem(word1)->documents[j].count;
                temp1.documentName=Htable.getItem(word1)->documents[j].documentName;
                //store each doc and count to print
                x1.push_back(temp1);
            }
            storealltable.push_back(x1);
        }
        else{
            //that word does not exist in the tree so need to display no document
            //cout<<"No document contains the given query"<<endl;
            nodoc1=true;
        }
        int indexvector=binarySearch(initial,word1);
        if(indexvector!=-1){
            int s =initial[indexvector].documents.size();
            for(int j=0;j<s;j++){
                DocumentItem temp1;
                temp1.count=initial[indexvector].documents[j].count;
                temp1.documentName=initial[indexvector].documents[j].documentName;
                x1.push_back(temp1);
            }
            storeallvector.push_back(x1);
        }
        else{
            nodoc2=true;
        }
    }

    if(nodoc){

        cout<<"No document contains the given query"<<endl;
    }
    else{
        for(int i=0;i<storefiles.size();i++){
            //we need to check if all words in query are in that document to print if not dont print that document
            if(inDoc(storealltree,storefiles[i])){

                cout<<"in Document "+storefiles[i];
                for(int j=0;j<storewords.size();j++){
                    for(int k=0;k<storealltree[j].size();k++){
                        if(storealltree[j][k].documentName==storefiles[i]){
                            cout<<", ";
                            string word1=storewords[j];
                            //ToLower(word);
                            cout<<word1+" found "+to_string(storealltree[j][k].count)+" times";
                        }
                    }
                }
                cout<<"."<<endl;
            }

        }
    }
    if(nodoc1){

        cout<<"No document contains the given query"<<endl;
    }
    else{
        for(int i=0;i<storefiles.size();i++){
            //we need to check if all words in query are in that document to print if not dont print that document
            if(inDoc(storealltable,storefiles[i])){

                cout<<"in Document "+storefiles[i];
                for(int j=0;j<storewords.size();j++){
                    for(int k=0;k<storealltable[j].size()/2;k++){
                        if(storealltable[j][k].documentName==storefiles[i]){
                            cout<<", ";
                            string word1=storewords[j];
                            //ToLower(word);
                            cout<<word1+" found "+to_string(storealltable[j][k].count)+" times";
                        }
                    }
                }
                cout<<"."<<endl;
            }

        }
    }

    if(nodoc2){

        cout<<"No document contains the given query"<<endl;
    }
    else{
        for(int i=0;i<storefiles.size();i++){
            //we need to check if all words in query are in that document to print if not dont print that document
            if(inDoc(storeallvector,storefiles[i])){
                cout<<"in Document "+storefiles[i];
                for(int j=0;j<storewords.size();j++){
                    int check=(storeallvector[j].size()/2)-1;
                    if (check==0){
                        check=1;
                    }
                    for(int k=0;k<check;k++){
                        if(storeallvector[j][k].documentName==storefiles[i]){
                            cout<<", ";
                            string word1=storewords[j];
                            //ToLower(word);
                            cout<<word1+" found "+to_string(storeallvector[j][k].count)+" times";
                        }
                    }
                }
                cout<<"."<<endl;
            }
        }
    }


   int k = 100; /// TODO change to 100
    clock_t begin_time = clock();
    for (int i = 0; i < k; i++)
        QueryTree(storefiles,storewords,tree);
        double endBST = float(clock() - begin_time);
    cout << "\nBinary Search Tree Time: " << endBST / k << "\n";
    begin_time = clock();
    for (int i = 0; i < k; i++)
        QueryTable(storefiles,storewords,Htable);
        double endHT = float(clock() - begin_time);
    cout << "\nHash Table Time: " << endHT / k << "\n";
    begin_time = clock();
    for (int i = 0; i < k; i++)
        Binary(storefiles,storewords,initial);
        double endBS = float(clock() - begin_time);
    cout << "\nBinary Search Time: " << endBS / k << "\n";
    cout<<endl;
    begin_time = clock();

        quicksortWithMedianPivot(sortvec1,0,sortvec1.size()-1);

    double endQSM = float(std::difftime(clock(), begin_time));
    //cout << endQSM << endl;
    cout << "\nQuick Sort(median) Time: " << endQSM / k << "\n";

    begin_time = clock();

        quicksortWithRandomPivot(sortvec2,0,sortvec2.size()-1);
        double endQSR = float(std::difftime(clock(), begin_time));
    cout << "\nQuick Sort(random) Time: " << endQSR / k << "\n";
    begin_time = clock();

        quicksortWithFirstElementPivot(sortvec3,0,sortvec3.size()-1);
        double endQSF = float(clock() - begin_time);
    cout << "\nQuick Sort(first) Time: " << endQSF / k << "\n";
    begin_time = clock();

        mergeSort(sortvec4,0,sortvec4.size()-1);
        double endM = float(clock() - begin_time);
    cout << "\nMerge Sort Time: " << endM / k << "\n";
    begin_time = clock();

        heapsort(sortvec5);
        double endH = float(clock() - begin_time);
    cout << "\nHeap Sort Time: " << endH / k << "\n";
    begin_time = clock();

        insertionSort(sortvec6);
        double endI = float(clock() - begin_time);
    cout << "\nInsertion Sort Time: " << endI / k << "\n";

    /*int k = 100;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        QueryTree(storefiles,storewords,tree);

    }
    auto endBST = chrono::duration_cast<chrono::nanoseconds>
            (chrono::high_resolution_clock::now() - start);
    cout << "\nBinary Search Tree Time: " << endBST.count() / k << "\n";
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        QueryTable(storefiles,storewords,Htable);
    }
    auto endHT = chrono::duration_cast<::chrono::nanoseconds>
            (chrono::high_resolution_clock::now() - start);
    cout << "\nHash Table Time: " << endHT.count() / k << "\n";

    for (int i = 0; i < k; i++)
    {
        Binary(storefiles,storewords,initial);
    }
    auto endBS = chrono::duration_cast<::chrono::nanoseconds>
            (chrono::high_resolution_clock::now() - start);
    cout << "\nBinary Search Time: " << endBS.count() / k << "\n";

    cout<<"//all timings are in nanoseconds, it will take a while for the timing values for the sort functions to appear"<<endl;

        quicksortWithMedianPivot(sortvec1,0,sortvec1.size()-1);

    auto endQSM = chrono::duration_cast<::chrono::nanoseconds>
            (chrono::high_resolution_clock::now() - start);
    cout << "\nQuick Sort(median) Time: " << endQSM.count() / k << "\n";


        quicksortWithRandomPivot(sortvec2,0,sortvec2.size()-1);

    auto endQSR = chrono::duration_cast<::chrono::nanoseconds>
            (chrono::high_resolution_clock::now() - start);
    cout << "\nQuick Sort(random) Time: " << endQSR.count() / k << "\n";


        quicksortWithFirstElementPivot(sortvec3,0,sortvec3.size()-1);

    auto endQSF = chrono::duration_cast<::chrono::nanoseconds>
            (chrono::high_resolution_clock::now() - start);
    cout << "\nQuick Sort(first) Time: " << endQSF.count() / k << "\n";


        mergeSort(sortvec4,0,sortvec4.size()-1);

    auto endM = chrono::duration_cast<::chrono::nanoseconds>
            (chrono::high_resolution_clock::now() - start);
    cout << "\nMerge Sort Time: " << endM.count() / k << "\n";


        heapsort(sortvec5);

    auto endH = chrono::duration_cast<::chrono::nanoseconds>
            (chrono::high_resolution_clock::now() - start);
    cout << "\nHeap Sort Time: " << endH.count() / k << "\n";


        insertionSort(sortvec6);

    auto endI = chrono::duration_cast<::chrono::nanoseconds>
            (chrono::high_resolution_clock::now() - start);
    cout << "\nInsertion Sort Time: " << endI.count() / k << "\n";*/



    //add the speedups
   /* cout<<endl;
    cout << "Speed Up BST/HST: " << double((endBST.count() / k))/(endHT.count() / k) << "\n";
    cout << "Speed Up Merge Sort/Quick Sort(Median): " << double((endM.count() / k))/(endQSM.count() / k) << "\n";
    cout << "Speed Up Heap Sort/Quick Sort(Median): " << double((endH.count() / k))/(endQSM.count() / k) << "\n";
    cout << "Speed Up Insertion Sort/Quick Sort(Median): " << double((endI.count() / k))/(endQSM.count() / k) << "\n";
    cout<<endl;
    cout << "Speed Up Binary Search / Binary Search Tree Time: " << double((endBS.count() / k))/(endBST.count() / k) << "\n";
    cout << "Speed Up Binary Search / Hash Table Time: " << double((endBS.count() / k))/(endHT.count() / k) << "\n";*/

    return 0;
}
