#ifndef VERTEXTABLE_H
#define VERTEXTABLE_H

namespace GraphCore{
    class VertexTable;

    class VertexTableDestroyer
    {
      private:
        VertexTable* p_instance;
      public:
        ~VertexTableDestroyer();
        void initialize(VertexTable* p);
    };

    class VertexTable
    {

      private:
        static VertexTable* p_instance;
        static VertexTableDestroyer destroyer;

      protected:
        VertexTable() { }
        VertexTable(const VertexTable&);
        VertexTable& operator=(VertexTable&);
       ~VertexTable() { }
        friend class VertexTableDestroyer;

      public:
        static VertexTable& getInstance();
    };
}

#endif // VERTEXTABLE_H
