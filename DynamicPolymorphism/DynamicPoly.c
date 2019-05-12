

int main(){

// class A { public: int data; virtual int GetData(){return data;} };
typedef struct A { void**vtable; int data;} A;
int AGetData(A*this){ return this->data; }
void * Avtable[] = { (void*)AGetData };
A * newA() { A*res = malloc(sizeof(A)); res->vtable = Avtable; return res; }

// class B : public class A { public: int moredata; virtual int GetData(){return data+1;} }
typedef struct B { void**vtable; int data; int moredata; } B;
int BGetData(B*this){ return this->data + 1; }
void * Bvtable[] = { (void*)BGetData };
B * newB() { B*res = malloc(sizeof(B)); res->vtable = Bvtable; return res; }
// int temp = ptr->GetData();


int temp = ((int(*)())ptr->vtable[0])();
//Then a dynamic cast is something like:

// A * ptr = new B();
A * ptr = (A*) newB();
// B * aB = dynamic_cast<B>(ptr);
B * aB = ( ptr->vtable == Bvtable ? (B*) aB : (B*) 0 );

return (0);
}
