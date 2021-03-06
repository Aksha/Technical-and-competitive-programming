#include <iostream>
#include <cstdlib>
#include <new>
#include <cstring>
#include <algorithm>

#define A 54059 /* prime */
#define B 76963 /* prime */
#define C 86969 /* prime */
#define first 37 /* prime */


struct record_t {
	char key[1024];
	int value1;
	int value2;
	record_t() {}
	~record_t() {}
};

class HashEntry {
	private:
	      char keyHash[1024];
	      record_t* r = new record_t();
	      HashEntry* next;
	      HashEntry* prev;
	public:
	      HashEntry(char k[1024], record_t* record) {
			std::strcpy(this->keyHash, k);
			this->r = record;
			this->next = NULL;
			this->prev = NULL;
	      }

	      const char* 
	      getKey()
	      {
	      	        return this->keyHash;
	      }

	      record_t*
	      getValue() 
	      {
		        return r;
	      }

	      void 
	      setValue(record_t* value) 
	      {
		 	this->r = value;
	      }

	      HashEntry* 
	      getNext() {
			return next;
	      }

	      void 
	      setNext(HashEntry* next) 
	      {
			this->next = next;
	      }
	      
	      
};

const int TABLE_SIZE = 100;

class HashMap {
private:
      HashEntry** table;
public:

      HashMap() {
	    try {
            	table = new HashEntry*[TABLE_SIZE];
            }
            catch (const std::bad_alloc& e) {
		std::cout << "Out of memory: " << e.what() << std::endl;
		exit(1);
	    }
            for (unsigned long long i = 0; i < TABLE_SIZE; i++) {
                  table[i] = NULL;
  	    }
      }

      ~HashMap() {
            for (int i = 0; i < TABLE_SIZE; i++)
                  if (table[i] != NULL) {
                        HashEntry *prevEntry = NULL;
                        HashEntry *entry = table[i];
                        while (entry != NULL) {
                             prevEntry = entry;
                             entry = entry->getNext();
                             delete prevEntry;
                        }
                  }
            delete[] table;
      }

	unsigned long long 
	hashFunction (std::string s)
	{
   		unsigned long long h = first;
   		int i = 0;
   		int length = s.size();
     		while (i < length) {
     			h = (h * A) ^ (s[i] * B);
     			i++;
   		}
   		return h % TABLE_SIZE;
	}

	void 
	insert (char key[1024], void* r, long unsigned size) 
	{
		record_t* record = new record_t;
		memcpy(record, r, size);
		unsigned long long hash = hashFunction(key);
		if (table[hash] == NULL) {
			table[hash] = new HashEntry(key,record);
		}
		else {
			HashEntry* entry = table[hash];
			while (entry->getNext() != NULL) {
				entry = entry->getNext();
			}	
			if (std::strcmp(entry->getKey(),key) == 0) {
				entry->setValue(record);
			}
			else {
				entry->setNext(new HashEntry(key,record));
			}
		}
	}

	record_t* 
	find (char key[1024]) 
	{
	    unsigned long long hash = hashFunction(key);
            if (table[hash] == NULL) {
                  return NULL;
	    }
            else {
                  HashEntry* entry = table[hash];	
                  while (entry != NULL && (std::strcmp(entry->getKey(), key) != 0)) {
                        entry = entry->getNext();
		  }
		  try {
			if (entry != NULL) {
				return entry->getValue();
			}
		  }
		  catch (std::exception& e) {
         	       std::cout << "bad things happened" << e.what() << std::endl;
                       exit(1);
        	  }
            }
	}

	void 
	remove (char key[1024]) 
	{
		unsigned long long hash = hashFunction(key);
		if (table[hash] != NULL) {
			HashEntry* prevEntry = NULL;
			HashEntry* entry = table[hash];
			while (entry->getNext() != NULL && (std::strcmp(entry->getKey(),key) != 0)) {
				prevEntry = entry;
				entry = entry->getNext();		
			}
			if (std::strcmp(entry->getKey(),key) == 0) {
				if (prevEntry == NULL) {
					HashEntry* nextEntry = entry->getNext();
					delete entry;
					table[hash] = nextEntry;
				}
				else {
					HashEntry* nextEntry = entry->getNext();
					delete entry;
					prevEntry->setNext(nextEntry);
				}
			}
		}
	}
};

void
test(HashMap* h) 
{
	record_t y;
	std::strcpy(y.key, "Hello there");
	y.value1 = 1;
	y.value2 = 2;
	try
	{
		h->insert(y.key, &y, sizeof(record_t));
	}
	catch (std::exception &e) 
	{
		std::cout << "Bad things Happened" << e.what() << std::endl;
	}
	try 
	{	
		record_t* rec_copy = h->find(y.key);
		std::cout << "After a quick SEARCH, the key is : " << rec_copy->key << " value1 is : "  << rec_copy->value1 << " value 2 is: "  << rec_copy->value2 << std::endl;
	}
	catch (std::exception &e)  
	{
		std::cout << "Bad things Happened" << e.what() << std::endl;
	}
	try 
	{
		h->remove(y.key);
	}
	catch(std::exception &e)
	{
		std::cout << "Bad things happened" << e.what() << std::endl;
	}
}

void
test_function() {
	HashMap* h = new HashMap();
	test(h);
	delete h;
}

int 
main()
{
	test_function();
	return 0;
}
