#ifndef BST_AND_HASH_SEARCH_ENGINE_HASHTABLE_H
#define BST_AND_HASH_SEARCH_ENGINE_HASHTABLE_H
#include <iostream>
#include <vector>

using namespace std;

template <class Key, class Value>
class HashTable {
private:
    struct Node {
        Key key;
        Value *value;

        Node(Key k, Value *v) {
            key = k;
            value = v;
        }
    };
    int size;
    int elements=0;
    vector<vector<Node>> table;
    int mod;
    double loadfactor=0;

    bool isPrime( int n )
    {
        if ( n == 2 || n == 3 )
            return true;

        if ( n == 1 || n % 2 == 0 )
            return false;

        for ( int i = 3; i * i <= n; i += 2 )
            if ( n % i == 0 )
                return false;

        return true;
    }

    int nextPrime( int n )
    {
        if ( n % 2 == 0 )
            n++;

        for ( ; ! isPrime( n ); n += 2 )
            ;

        return n;
    }

    /// Hash function to determine the index in the array
    int hash(const Key& key) const {
        unsigned int hashVal = 0;

        for (char c : key) {
            hashVal = 31 * hashVal + c; // multiply with random prime number 31 and add ascii value of each character
        }
        unsigned int hashValue=hashVal % mod;
        //cout << "Hash value for key '" << key << "': " << hashValue << endl;
        return hashValue;
    }
    /// Rehash the table when the load factor exceeds the specified range
    void rehash() {
        //cout<<"rehashed..."<<endl;
        //cout<<"previous table size: "<<table.size();

        int newSize = nextPrime(table.size() * 2); // next prime of Double the size for rehashing
        mod=newSize;
        vector<vector<Node>> newTable(newSize);

        // Move nodes from the old table to the new table using new hash values
        for (int i = 0; i < table.size(); ++i) {
            vector<Node>& bucket = table[i];
            for (int j = 0; j < bucket.size(); ++j) {
                int newIndex = hash(bucket[j].key);
                newTable[newIndex].push_back(bucket[j]);
            }
        }

        //update the hashtable
        table=newTable;
        //cout<<", new table size: "<<table.size()<<", current unique word count "<<elements<<","<<endl;
        loadfactor=double(elements)/newSize;
        //cout<<"current load factor: "<< loadfactor <<endl;
    }
public:
    HashTable(int initialSize ) : size(0) {
        table.resize(initialSize);
        mod= initialSize;
    }

    ~HashTable();
    bool find( const Key & key) const;
    void insert(const Key& key, Value* value);
    Value* getItem(const Key& key) const;
    void printTable() const;
    void after() const;



};

#endif
template <class Key, class Value>
HashTable<Key, Value>::~HashTable() {

    for (int i = 0; i < table.size(); i++) {
        table[i].clear();
    }
    table.clear();
}
template <class Key, class Value>
bool HashTable<Key, Value>::find(const Key& key) const {
    int index = hash(key);
    vector<Node> bucket = table[index];

    for(int i=0;i<bucket.size();i++){
        if(bucket[i].key==key){
            return true;
        }
    }
    return false;
}

template <class Key, class Value>
void HashTable<Key, Value>::insert(const Key& key, Value* value) {
    int hashVal = hash(key);
    //cout << "Inserting key: " << key << " with hash value: " << hashVal << endl;
    Node temp= Node(key,value);
    table[hashVal].push_back(temp);
    elements++;
    size++;

    double currentLoadFactor = double(size) / table.size();

    // Check if rehashing is needed
    if (currentLoadFactor >  0.75 ) {
        rehash();
    }


}

template <class Key, class Value>
Value* HashTable<Key, Value>::getItem(const Key& key) const {
    int index = hash(key);
    vector<Node> bucket = table[index];

    for(int i=0;i<bucket.size();i++){
        if(bucket[i].key==key){
            return bucket[i].value;
        }
    }
    return NULL; // Key not found
}


template <class Key, class Value>
void HashTable<Key, Value>::printTable() const {
    for (int i = 0; i < table.size(); ++i) {
        cout << "Bucket " << i << ": ";
        vector<Node> bucket = table[i];
        for(int j=0;j<bucket.size();j++){
            cout << "(" << bucket[j].key << ", "  << ") ";
        }
        cout << endl;
    }
}

template <class Key, class Value>
void HashTable<Key, Value>::after() const {
    cout<<"After preprocessing, the unique word count is "<<elements<<". Current load ratio is "<<loadfactor<<endl;

}