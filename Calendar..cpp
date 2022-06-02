/*
    Team members:
            Name, ID, Project Group Number & Name
        1-Sadeem Ali Aldossary 2210003590
        2-Reema Ahmed Alzahrani 2210003692
        3-Fai Rashid Aldossary 2210003654
        4-Layan Saleh Alkhamis 2210003583
*/
// Project Name: Calendar C++ Project
#include<iostream>
#include<ctime>
#include<fstream>
#include<cstring>

using namespace std;

// Global variables
const int txtSize=50;

struct noteStruct {
    int id;
    char noteText[txtSize];
    int noteDay;
    int noteMonth;
    int noteYear;
};

// Program functions are declared here
int functions(); // i.e. our program menu
void addNote();
void searchMemo();
void updateMemo();
void deleteMemo(noteStruct &xNote, int loc);
void sortMemo();
void putData(noteStruct &xNote);
void invalidMessage();

//*********************************************************************
int main(){

    int exitCode=0;
    int rno=1;
    noteStruct readNotes;

	// declare binary file stream.
	fstream fio;

	cout<<endl<<endl;
	cout <<"\t\t\t* * * * * * * * * * * * * * * *"<<endl;
	cout <<"\t\t\t<<< Welcome to Pro Calendar >>>"<<endl;
    cout <<"\t\t\t* * * * * * * * * * * * * * * *"<<endl;
    do{
       	cout <<endl<<endl;
       	cout <<"\t\t\t----------------------------"<<endl;
        cout <<"\t\t\t<<< Pro Calendar Options >>>"<<endl;
        cout <<"\t\t\t----------------------------"<<endl;
        switch(functions()){
        case 1:
            cout<<"\t\t\t<<< Add a new event or appointment >>>"<<endl;
            cout<<"\t\t\t--------------------------------------"<<endl;
            addNote();
            break;
        case 2:
            cout<<"\t\t\t<<< Search for a specific event/ appointment >>>"<<endl;
            cout<<"\t\t\t-------------------------------------------"<<endl;
            searchMemo();
            break;
        case 3:
            cout<<"\t\t\t<<< Update a specific event/ appointment >>>"<<endl;
            cout<<"\t\t\t-------------------------------------------"<<endl;
            updateMemo();
            break;
        case 4:
            cout<<"\t\t\t<<< Delete an event/ appointment >>>"<<endl;
            cout<<"\t\t\t------------------------------------"<<endl;
            fio.open("myNotes.dat", ios::binary | ios::app);
           	if(! fio.is_open()){
                cout<<"### File does not exist ###"<<endl;
                cout<<"### Please Add Memos first ###";
            }else{
                cout<<"\t\t\t >> Which Event number to DELETE: ";
                cin>>rno;
                deleteMemo(readNotes, rno);
            }
            fio.close();

            break;
        case 5:
            cout<<"\t\t\t<<< Your events Sorted >>>"<<endl;
            cout<<"\t\t\t--------------------------"<<endl;
                sortMemo();
            break;
        case 6:
            cout<<"\t\t\t<<< Display all events and appointments >>>"<<endl;
            cout<<"\t\t\t-------------------------------------------"<<endl;
            cout<<"\tHere is a list of your Memos:"<<endl;
            cout<<"\t-----------------------------"<<endl;
            fio.open("myNotes.dat", ios::binary | ios::in);
           	if(! fio.is_open()){
                cout<<"### File does not exist ###"<<endl;
                cout<<"### Please Add Memos first ###";
            }else{
                fio.seekg(0);
                while(!fio.eof()){
                    fio.read((char*)&readNotes, sizeof(readNotes));
                    if (fio.eof()){
                        // do nothing - in order not to repeat the last memo
                    }else
                        putData(readNotes);
                }
                fio.close();
            } // else
            break;
        case 7:
            exitCode = 7;
            break;
        default:
            invalidMessage();
        } // end of switch (functions())
    } while (exitCode != 7);
cout<<endl;
cout<<"\t\t\t--------------------------------"<<endl;
cout<<"\t\t\tThank you for using Pro Calendar"<<endl;
cout<<"\t\t\t     We wish you a good day"<<endl;
cout<<"\t\t\t--------------------------------"<<endl;
} // main() ends here
//*********************************************************************


//**************** Functions are implemented here ****************

int functions(){
    int choice;
    cout<<"\t\t1- Add a new event/ appointment."<<endl;
    cout<<"\t\t2- Search for a specific event/ appointment."<<endl;
    cout<<"\t\t3- Update an existing event/ appointment."<<endl;
    cout<<"\t\t4- Delete an existing event/ appointment."<<endl;
    cout<<"\t\t5- Sort entries."<<endl;
    cout<<"\t\t6- Display all entries."<<endl;
    cout<<"\t\t7- Exit Calendar services."<<endl;
    cout<<"\n\t\t\tEnter your choice(1-7) >> ";
    cin>> choice;
    cout<<endl<<endl;
 return choice;
} // int functions()
//*********************************************************************

void invalidMessage(){
   cout<<endl;
   cout<<"\t*** Invalid Choice. ***"<<endl;
   cout<<"\t*** Available choices are 1 through 7 ***"<<endl;
   cout<<endl;
} // void invalidMessage()
//*********************************************************************

void addNote(){
    fstream fio;
    noteStruct xNote;
    char correct='n';
    // the next line is to capture the extra "Enter key" from the previous entry.
    // there is no other uses to variable x.
    // string x; getline(cin,x);

    cout<<"\t\t\t>> Please enter Note * No.: ";
    cin>>xNote.id;
    cout<<"\t\t\t>> Please enter your Note: ";
        // getline(cin, xNote.noteText);
        // cin.getline(xNote.noteText,txtSize);
    cin>>xNote.noteText;

    cout<<"\t\t\tPlease enter Day, Month and Year, respectively:"<<endl;
    while (correct != 'y'){
        cout<<"\t\t\t >> Enter Day: ";
        cin>>xNote.noteDay;
        if (xNote.noteDay <1 || xNote.noteDay > 31)
            cout<<"\t\t\t ### Invalid entry, Days are 1 through 31 max:"<<endl;
        else
            correct = 'y';
    }// while (correct != 'y')

    correct = 'n';
    while (correct != 'y'){
        cout<<"\t\t\t >> Enter Month: ";
        cin>>xNote.noteMonth;
        if (xNote.noteMonth < 1 || xNote.noteMonth > 12)
            cout<<"\t\t\t ### Invalid entry, Months are 1 through 12 max:"<<endl;
        else
            correct = 'y';
    }// while (correct != 'y')
    cout<<"\t\t\t >> Enter Year: ";
    cin>>xNote.noteYear;

    //open for append to make sure it exists.
    fio.open("myNotes.dat", ios::binary | ios::app);
    if(! fio.is_open())
        cout<<"### Could not open file ###";
    else{
        // save the values
        // fileObjectName.write( memory location , size of dataType);
        fio.write( (char*)&xNote, sizeof(xNote)); // to save to disk
        cout<<"\t<<< NOTE SAVED TO DISk>>>";
        fio.close();
    }
} // void addNote(noteStruct xNote)
//*********************************************************************

void searchMemo(){
    int rno;
    long pos;
    char found='f';
    noteStruct xNote;
    fstream fio;
    // ios::in is to read from file
    fio.open("myNotes.dat", ios::binary | ios::in);
    if(! fio.is_open()){
        cout<<"### File does not exist ###"<<endl;
        cout<<"### Please Add Memos first ###";
    }else{
        cout<<"\t\t\t >> Enter Event number to find: ";
        cin>>rno;
        fio.seekg(0);
        while(!fio.eof()){
            pos=fio.tellg();
            fio.read((char*)&xNote, sizeof(xNote));
            if(xNote.id == rno && !fio.eof() ){
                cout<<"\t\t\t\t>>"<<xNote.id;
                cout<<"\t>>"<<xNote.noteText;
                cout<<"\ton "<<xNote.noteDay;
                cout<< "/ "<<xNote.noteMonth;
                cout<<"/ "<<xNote.noteYear<<endl;
                found = 't';
            }
        } // while
        if (found=='f'){
            cout<<"\t\t\t\t### Can't find Memno * No. "<<rno<<" ###"<<endl;
        }
    fio.close();
    } // else
} // void searchMemo(noteStruct xNote, int pos)
//*********************************************************************

void updateMemo(){
    int rno;
    long pos;
    char found='f';
    char correct='n';
    noteStruct xNote;
    fstream fio;
    fio.open("myNotes.dat", ios::binary | ios::in | ios::out);
    if(! fio.is_open()){
        cout<<"### File does not exist ###"<<endl;
        cout<<"### Please Add Memos first ###";
    }else{
        cout<<"\t\t\t >> Enter Event number to update: ";
        cin>>rno;
        fio.seekg(0);
        while(!fio.eof()){
            pos=fio.tellg();
            fio.read((char*)&xNote, sizeof(xNote));
            if(xNote.id == rno){
                cout<<"\t\t\t\t>>"<<xNote.id;
                cout<<"\t>>"<<xNote.noteText;
                cout<<"\ton "<<xNote.noteDay;
                cout<< "/ "<<xNote.noteMonth;
                cout<<"/ "<<xNote.noteYear<<endl;
                found = 't';

                // update starts here,
                fio.seekp(pos);
                cout<<"\t\t\t\t<<< UPDATE THIS NOTE >>>"<<endl;
                cout<<"\t\t\t\t-------------------------"<<endl;
                cout<<"\t\t\t\t >> Please UPDATE Note * No.: ";
                cin>>xNote.id;
                cout<<"\t\t\t\t >> Please UPDATE your Note: ";
                cin>>xNote.noteText;

                cout<<"\t\t\t\tPlease UPDATE Day, Month and Year, respectively:"<<endl;
                while (correct != 'y'){
                    cout<<"\t\t\t\t >> UPDATE Day: ";
                    cin>>xNote.noteDay;
                    if (xNote.noteDay <1 || xNote.noteDay > 31)
                        cout<<"\t\t\t ### Invalid entry, Days are 1 through 31 max:"<<endl;
                    else
                        correct = 'y';
                }// while (correct != 'y')

                correct = 'n';
                while (correct != 'y'){
                    cout<<"\t\t\t\t >> UPDATE Month: ";
                    cin>>xNote.noteMonth;
                    if (xNote.noteMonth < 1 || xNote.noteMonth > 12)
                        cout<<"\t\t\t ### Invalid entry, Months are 1 through 12 max:"<<endl;
                    else
                        correct = 'y';
                }// while (correct != 'y')
                cout<<"\t\t\t\t >> UPDATE Year: ";
                cin>>xNote.noteYear;

                // now save the new data
                fio.write((char*)&xNote, sizeof(xNote));
                cout<<"\t<<< NOTE UPDATED >>>";
            } //if xNote.id = rno
        } // while (! fio.eof())
        fio.close();
        if (found=='f'){
            cout<<"\t\t\t\t### Can't find Memno * No. "<<rno<<" ###"<<endl;
        }
    } // else -- enter the event number to update
} // void updateMemo(noteStruct xNote, int pos)
//*********************************************************************

void deleteMemo(noteStruct &xNote, int loc){
    /*  The idea is to read the records from the file
        in an array of struct, except the targeted ones.
        Then write the array of struct to the same file.
    */
    int pos=0;
    char found='f';
    int recordsCount=1;
    fstream fio;
    // open the file for reading only
    // read the file to find out the total number of records
    fio.open("myNotes.dat", ios::binary | ios::in);
    fio.seekg(0);
    while(!fio.eof()){
        fio.read((char*)&xNote, sizeof(xNote));
        recordsCount++;
    }
    fio.close();

    // declare the total number of records must be const int
    const int recCount = recordsCount;

    // declare an array of records
    noteStruct newNote[recCount];

    // start reading process
    // open file for reading only.
    // open the file and read with filtering the records.
    fio.open("myNotes.dat", ios::binary | ios::in);
    fio.seekg(0);
    recordsCount=1;
    while(!fio.eof()){
        fio.read((char*)&xNote, sizeof(xNote));
        if(xNote.id != loc && !fio.eof()){
            // assign the desired records only to the array of records
            newNote[pos].id = xNote.id;
            // because this field is an array, we must use strcpy()
            // not the assignment operator =
            strcpy(newNote[pos].noteText, xNote.noteText);
            newNote[pos].noteDay = xNote.noteDay;
            newNote[pos].noteMonth = xNote.noteMonth;
            newNote[pos].noteYear = xNote.noteYear;
            pos++;
            recordsCount++; // keep track of the new number of records
        }
        if(xNote.id == loc){
            found ='t';
        }
    } // while reading the struct array
    fio.close();

    // start writing process

    if (found == 't'){
        // The record was found, start the writing process
        // open file for write only
        // write / save the new records.
        pos = 0;
        fio.open("myNotes.dat", ios::binary | ios::out);
        fio.seekp(0);
        // save / write the new number of records to the same file.
        while(pos < recordsCount-1){
            xNote.id = newNote[pos].id;
            // because this field is an array, we must use strcpy()
            // not the assignment operator =
            strcpy(xNote.noteText, newNote[pos].noteText);
            xNote.noteDay = newNote[pos].noteDay;
            xNote.noteMonth = newNote[pos].noteMonth;
            xNote.noteYear = newNote[pos].noteYear;
            pos++;
            fio.write((char*)&xNote, sizeof(xNote));
        }// while writing the xNote
        fio.close();
        cout<<"\t<<< NOTE DELETED >>>";
    }else{
        cout<<"\t\t\t\t### Can't find Memno * No. "<<loc<<" ###"<<endl;
    }
} // void deleteMemo(noteStruct xNote, int pos)
//*********************************************************************

void sortMemo(){
    int pos=0;
    char found='f';
    int recordsCount=1;
    noteStruct tempNote;
    noteStruct xNote;
    fstream fio;
    // open the file for reading only
    // read the file to find out the total number of records
    fio.open("myNotes.dat", ios::binary | ios::in);
    if(! fio.is_open()){
        cout<<"### File does not exist ###"<<endl;
        cout<<"### Please Add Memos first ###";
    }else{
        fio.seekg(0);
        while(!fio.eof()){
            fio.read((char*)&xNote, sizeof(xNote));
            recordsCount++;
        }
        fio.close();

        // declare the cumber of records
        const int recCount = recordsCount;
        // declare an array of records
        noteStruct newNote[recCount];

        // open file for read only.
        // open the file and read with filtering the records.
        fio.open("myNotes.dat", ios::binary | ios::in);
        // put the file pointer at the beginning of file
        fio.seekg(0);
        // read the file contents into array struct in memory
        while(!fio.eof()){
            fio.read((char*)&xNote, sizeof(xNote));
            newNote[pos].id = xNote.id;
            // because this field is an array, we must use strcpy()
            // not the assignment operator =
            strcpy(newNote[pos].noteText, xNote.noteText);
            newNote[pos].noteDay = xNote.noteDay;
            newNote[pos].noteMonth = xNote.noteMonth;
            newNote[pos].noteYear = xNote.noteYear;
            recordsCount = pos++; // keep track of the new number of records
          } // while reading the struct array
        fio.close();

        // 2 for loops to sort the structs
        for(int i = 0; i < recordsCount ;i++){
            for (int j=i+1; j < recordsCount; j++ ){
                if(newNote[j].id < newNote[i].id){
                    // swap a struct with a struct.
                    tempNote = newNote[i];
                    newNote[i] = newNote[j];
                    newNote[j] = tempNote;
                }// if swap
            }// inner for
        } // outer for

        // Display the sorted array of struct; newNote.
        for(int i = 0; i < recordsCount ;i++){
            /////////////////////// cout<<newNote[i].id;
            cout<<"\tMemo * # "<<newNote[i].id;
            cout<<"\t"<<newNote[i].noteText;
            cout<<"\ton "<<newNote[i].noteDay<<" /";
            cout<<newNote[i].noteMonth<<" /"<<newNote[i].noteYear<<endl;
         }
    } // else start sort
}// void sortMemo(noteStruct xNote)
//*********************************************************************

void putData(noteStruct &xNote){
    cout<<"\tMemo * # "<<xNote.id<<"\t"<<xNote.noteText;
    cout<<"\ton "<<xNote.noteDay<<" /";
    cout<<xNote.noteMonth<<" /"<<xNote.noteYear<<endl;
} // void putData(noteStruct xNote)
//*********************************************************************

