#include <fstream>
#include <iostream>

using namespace std;


class Data
{
public:
    long key;
    string txt;
    long tries;
};


class Hash
{
private:
    Data** tab;
    int size;
public:
    Hash(int n);
    int hashFunction(int key);
    void insert(int key, string txt);
    void remove(int key);
    void printTable(const char* out);
    void removeTab();
};



Hash::Hash(int n)
{
    size = n;
    tab = new Data*[n];
    for (int i = 0; i < n; i++)
    {
        tab[i] = NULL;
    }
}

int Hash::hashFunction(int key)
{
    return key % size;
}

void Hash::insert(int key, string txt)
{
    int index = hashFunction(key);
    int x=0;
    while (tab[index] != NULL)
    {
        if (index == size - 1)
            index = -1;
        index += 1;
        x++;

    }

    tab[index] = new Data();
    tab[index]->tries = x;
    tab[index]->key = key;
    tab[index]->txt = txt;

}

void Hash::remove(int key)
{
    int index = hashFunction(key);
    while (tab[index]->key != key)
    {
        if(index == size - 1)
            index = -1;
        index++;

    }

    delete tab[index];
    tab[index] = NULL;
    int i = index + 1;
    if (i == size)
        i = 0;
    while (i != index)
    {
        if (tab[i] != NULL)
        {
            int z = i - tab[i]->tries;
            if (z < 0)
                z = size + z;
            if (tab[z] == NULL && tab[i]->tries != 0)
            {
                
                tab[z] = new Data();
                tab[z]->tries = 0;
                tab[z]->txt = tab[i]->txt;
                tab[z]->key = tab[i]->key;
                delete tab[i];
                tab[i] = NULL;
            }
        }
        if (i == size - 1)
            i = -1;
        i++;
    }
    i = index + 1;
    while (i != index)
    {
        if (i == size)
            i = 0;
        if (tab[i] != NULL && tab[i]->tries != 0)
        {
            int temp = i - tab[i]->tries;
            if (temp < 0)
                temp = size + temp;
            if (temp == size)
                temp = 0;
            int temp2 = i - 1;
            if (temp2 < 0)
                temp2 = size - 1;
            int j = temp2;
            int z = 0;
            while (j != temp)
            {
                if (j == -1)
                    j = size - 1;
                if (tab[j] == NULL)
                {
                    if (tab[i] != NULL)
                    {
                        tab[j] = new Data();
                        tab[j]->tries = tab[i]->tries - (z + 1);
                        tab[j]->key = tab[i]->key;
                        tab[j]->txt = tab[i]->txt;
                        delete tab[i];
                        tab[i] = NULL;
                    }
                }
                z++;
                j--;
            }
        }
        i++;
    }

}

void Hash::printTable(const char* out)
{
    ofstream write(out,ios_base::app );
    if (write.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            if (tab[i] != NULL)
                write << i << " " << tab[i]->key << " " << tab[i]->txt << endl;
        }
        write << endl;
    }
    else
        cout << "ERROR2";
    write.close();
}



void Hash::removeTab()
{
    for (int i = 0; i < size; i++)
    {
        if (tab[i] != NULL)
        {
            delete tab[i];
        }
    }
    delete[] * tab;
}

void readFile(const char* in, const char* out)
{
    ifstream file(in);
    if (file.is_open())
    {
        int NoTests, key, size;
        string a, x, txt;
        file >> NoTests;
        for (int i = 0; i < NoTests; i++)
        {
            file >> a >> size;
            Hash tab(size);
            while (true)
            {               
                file >> x;
                if (x == "add")
                {
                    file >> key >> txt;
                    tab.insert(key, txt);
                }
                else if (x == "stop")
                {   
                    tab.removeTab();
                    break;
                }
                else if (x == "delete")
                {
                    file >> key;
                    tab.remove(key);
                }
                else if (x == "print")
                {
                    tab.printTable(out);
                }
            }
        }

    }
    else
        cout << "ERROR1";
    file.close();
}

int main()
{
    readFile("in.txt", "out.txt");

    return 0;
}
