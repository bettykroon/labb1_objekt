#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

struct Location;
struct Person;
vector<Person> file(const string &filename);
size_t sokNamn(vector<Person>persons, string namn);
vector<Person> sokStad(vector<Person>städer, string stad);

struct Location 
{
    string gata;
    int postnr;
    string stad;
};

struct Person 
{
    string namn;
    string id;
    Location adress;
};

int main() 
{
    bool meny = true;
    string namn;

    while(meny)
    {
        cout << "---- MENY ----" << endl;
        cout << "1. Sök del av personnamn" << endl;
        cout << "2. Sök stad" << endl;
        cout << "3. Avsluta" << endl;

        int alt;
        cout << "Val: ";
        cin >> alt;

        vector<Person> p_vec;

        if(alt == 1)
        {
            p_vec = file("names.txt");

            cin.ignore();
            cout << "Skriv ett namn(börja med stor bokstav):" <<  endl;
            getline(cin, namn);

            size_t x = sokNamn( p_vec,namn );
            if(namn.length() != 0)
            {
                if(x > 0)
                {
                    cout << "Hittade "<< x << " person/personer vid det namnet" << '\n' << endl;
                    cout << "Tryck enter för att  komma tillbaka till menyn" << endl;
                    cin.ignore(1000,'\n');
                }
                else if(x == 0) 
                {
                    cout << "Hittade inga personer vid det namnet" << '\n' << endl;
                    cout << "Tryck enter för att  komma tillbaka till menyn" << endl;
                    cin.ignore(1000,'\n');
                }
            }
            else
            {
                cout << "Felaktig inmatning.." << '\n' << endl;
                cout << "Tryck enter för att  komma tillbaka till menyn" << endl;
                cin.ignore();
            }
        }

        if(alt == 2)
        {
            string stad;
            p_vec = file("names.txt");

            vector<Person>v;

            cin.ignore();
            cout << "Skriv en stad(med stora bokstäver):" << endl;
            getline(cin, stad);

            cout << "Personer som bor i " << stad << ":" << '\n' << endl;

            v = sokStad(p_vec, stad);
            
            for(unsigned int i = 0; i< v.size(); ++i)
            {
                cout << v[i].namn << endl;
            }

            if(v.size() == 0)
            {
                cout << "Kunde inte hitta någon i den staden" << endl;
            }

            cout << "Tryck enter för att  komma tillbaka till menyn" << endl;
            cin.ignore(1000,'\n');
        }

        if(alt == 3)
        {
            exit(0);
        }
    }
}

istream& operator >> (istream& is, Person& person)
{
	is >> person.namn;
	is >> person.id;
	is >> person.adress.gata;
	is >> person.adress.postnr;
	is >> person.adress.stad;
	
	return is;	
}

size_t sokNamn(vector<Person>personer, const string namn)
{
    size_t antal = 0;
    
    for(unsigned int i = 0; i < personer.size(); ++i)
    {
        if(personer[i].namn.find(namn) != string::npos)
        {
            antal++;        
        }
    }
    return antal;
}

vector <Person> sokStad(vector<Person>städer, string stad)
{
    vector<Person> v;
    Person person;
    string adress, namn;

    for(unsigned int i = 0; i < städer.size(); ++i)
    {
        adress = städer[i].adress.stad;

        if ( adress == stad )
        {
            person.namn = städer[i].namn;
            person.adress.stad = städer[i].adress.stad;
            v.push_back(person); 
        } 
    }
    return v;
}

vector <Person> file( const string &filename ) 
{
    vector <Person> p_vec;
    Person person;

    ifstream in;
    in.open( filename );

    if(!in.is_open())
    {
        cout << "Kunde inte öppna filen!" << endl;
        exit(0);
    }

    while(in.peek() != in.eof())
    {
        if(in.eof())
            break;

        getline(in, person.namn);
        getline(in, person.id);
        getline(in, person.adress.gata);

        string tmp = person.adress.gata;
        int pos = tmp.find(",");
        string gata = tmp.substr(0,pos);
        person.adress.gata = gata;

        string adress = tmp.substr(pos+1);
        istringstream iss(adress);

        string postnr1, postnr2, postnr_stad1, postnr_stad2;
        
        iss >> skipws >> postnr1 >> postnr2 >> postnr_stad1 >> postnr_stad2;
        string postnr = postnr1 + postnr2;

        string stad = postnr_stad1 + postnr_stad2;
        person.adress.stad = stad;
        
        int postnum = stoi(postnr);
        person.adress.postnr = postnum;

        p_vec.push_back( person );
    }
    return p_vec;
}