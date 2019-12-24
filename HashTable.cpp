#include <iostream>
#include <iomanip>
#include <stack>
#include <vector>
#include <cstdlib>
#include <ctime>


//Demonstrates hash table with linear probing


class DataItem
{ //Could have more data
public:
   int data; //Data item(key)
  DataItem(int newData)
  {
      data = newData;
  } //Constructor {}
}; //End Class DataItem


class HashTable
{
private:
   vector<DataItem*> hashArray; //Vector Holds main Hash Table
   int arraySize;
   DataItem* pNonItem; //for deleted items
public:
   HashTable(int size) //constructor
   {
       arraySize = size;
       hashArray.resize(arraySize); //size the vector
       for (int j=0; j<arraySize; j++) //initialize elements
       {
           hashArray[j] = NULL;
       }
       pNonItem = new DataItem(-1);
   }


   void displayTable()
   {
       cout << "Table: ";
       for (int j=0; j<arraySize; j++)
       {
           if (hashArray[j] != NULL)
               cout << hashArray[j]->data << " ";
           else
               cout << "**";
       }
       cout << endl;
   }


   int hashFunc(int key)
   {
       return key % arraySize; //hash function
   }


   void insert(DataItem* pItem) //Insert a DataItem
   //(assumes table not full)
   {
       int key = pItem->data; //Extract key
       int hashVal = hashFunc(key); //Hash the key
       //until empty cell or -1
       while (hashArray[hashVal] != NULL && hashArray[hashVal]->data != 1)
       {
           ++hashVal; //Go to next cell
           hashVal %= arraySize; //Wraparound if necessary
       }
       hashArray[hashVal] = pItem;
       //end insert()
   }


   DataItem* remove(int key) // Remove an item
   {
       int hashVal = hashFunc(key); //Hash the Key
       while(hashArray [hashVal] != NULL) //Until Empty Cell
       {
           if(hashArray[hashVal]->data == key) //Found the key?
           {
               DataItem *pTemp = hashArray[hashVal]; //Save Item
               hashArray[hashVal] = pNonItem; //Delete Item
               return pTemp; //Return item
           }
           ++hashVal; // Go to next cell
           hashVal %= arraySize; //Wraparound if necessary
       }
       return NULL;
   } //end remove()


   DataItem* find(int key) //Find item with key
   {
       int hashVal = hashFunc(key); //Hash the key
       while (hashArray[hashVal] != NULL) //Until empty cell
       {
           if (hashArray[hashVal]->data == key) //found the key?
               return hashArray[hashVal]; // Yes, return item
           ++hashVal; //Go to next cell
           hashVal %= arraySize; // Wraparound if necessary
       }
       return NULL;
   }
}; //end class HashTable


int main()
{
   DataItem* pDataItem;
   int aKey, size, n, keysPerCell;
   time_t aTime;
   char choice = 'b';
   //get sizes
   cout << "Enter size of hash table: ";
   cin >> size;
   cout << "Enter initial number of items: ";
   cin >> n;
   keysPerCell = 10;


   HashTable theHashTable(size); //Make Table
   srand (static_cast<unsigned>time(&aTime))); //make a random list of numbers
   for (int j=0; j<n; j++) //Insert Data
   {
       aKey = rand() % (keysPerCell*size); // r
       pDataItem = new DataItem(aKey);
       theHashTable.insert(pDataItem);
   }
   while (choice != 'x') //Interact with user
   {
       cout << "Enter first letter of "
            << "show, insert, delete or find: ";
       char choice;
       cin >> choice;
       switch(choice)
       {
           case 's':
               theHashTable.displayTable();
               break;
           case 'i':
               cout << "Enter key value to insert: ";
               cin >> aKey;
               pDataItem = new DataItem(aKey);
               theHashTable.insert(pDataItem);
               break;
           case 'd':
               cout << "Enter key value to delete: ";
               cin >> aKey;
               theHashTable.remove(aKey);
               break;
           case 'f':
               cout << "Enter hash value to find: ";
               cin >> aKey;
               pDataItem = theHashTable.find(aKey);
               if (pDataItem != NULL)
                   cout << "Found " << aKey << endl;
               else
                   cout << "Could not find " << aKey << endl;
               break;
           default:
               cout << "Invalid entry\n";
       } //End Switch
   } //End While
} End Main()