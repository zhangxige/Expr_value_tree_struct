#include <string>
#include <iostream>
using namespace std;
class Expr;

class Expr_node {
	friend class Expr;
        friend ostream& operator<<(ostream&, const Expr&);
	int use;
protected:
	Expr_node(): use(1) { }
        virtual void print(ostream&) const = 0;
        virtual int eval() const = 0;
        virtual ~Expr_node() { }
};

class Expr {
	friend class Expr_node;
	friend ostream& operator<<(ostream&, const Expr&);
	Expr_node* p;
public:
	Expr(int);
	Expr(const string&, Expr);
	Expr(const string&, Expr, Expr);
	Expr(const string&, Expr, Expr, Expr);       
	Expr(const Expr& t) { p = t.p; ++p->use; }
	~Expr() { if (--p->use == 0) delete p; }
	Expr& operator=(const Expr& t);
	int eval() const { return p->eval(); }
};

class Ternary_node: public Expr_node {
	friend class Expr;
	string op;
	Expr left;
	Expr middle;
	Expr right;
	Ternary_node(const string& a, 
		      Expr b, Expr c, Expr d):
		op(a), left(b), middle(c), right(d) { }
	void print(ostream& o) const 
	{
		o << "(" << left << " ? " <<
			middle << " : " << right << ")";
	}
	int eval() const;
};

class Unary_node: public Expr_node {
        friend class Expr;
        string op;
        Expr opnd;
        Unary_node(const string& a, Expr b):
                op(a), opnd(b) { }
        void print(ostream& o) const
                { o << "(" << op << opnd << ")"; }
	int eval() const;                          
};

class Int_node: public Expr_node {
        friend class Expr;
        int n;
        Int_node(int k): n(k) { }
        void print(ostream& o) const { o << n; }
	int eval() const { return n; }            
};

class Binary_node: public Expr_node {
	friend class Expr;
        string op;
        Expr left;
        Expr right;
        Binary_node(const string& a, Expr b, Expr c):
                op(a), left(b), right(c) { }
        void print(ostream& o) const
                { o << "(" << left << op << right << ")"; }
	int eval() const;
};
