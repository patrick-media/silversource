#include<iostream>
#include<string>

#define SS_NONE 0
#define SS_STR 1
#define SS_INT 2
#define SS_PRGM 3

void Parse( std::string cmd );
template< class type_All >
int ArraySize( type_All array[] );

bool RUN;
typedef struct ConCmd_s { // console command
    std::string name; // command name
    int argt; // argument type [ SS_NONE, SS_STR, SS_INT, SS_PRGM ]
    int argc; // argument count
    std::string arg[ 4 ]; // argument list
    std::string helpstring; // command help text
} ConCmd;
ConCmd ConCmdList[ 2 ] = {
    ConCmd{ "quit", SS_NONE, 0, "", "Quit the program" },
    ConCmd{ "help", SS_NONE, 0, "", "See a list of commands or specific help for certain commands" }
};
std::string PrgmList[ 2 ] = {
    "calculator", "test"
};
int ConCmdCount = ArraySize( ConCmdList );
int PrgmListCount = ArraySize( PrgmList );

int main( void ) {
    RUN = true;
    std::string input;
    while( RUN ) {
        std::cout<<">";
        std::cin>>input;
        Parse( input );
    }
    std::cout<<"Goodbye!"<<std::endl;
    #ifdef SS_DEBUG
    std::cout<<"debug line lol not yet finished"<<std::endl;
    #endif // SS_DEBUG
    return 0;
}
void Parse( std::string cmd ) {
    // TODO split into arguments
    bool CmdFound = false;
    int ListPos = -1;
    if( !CmdFound ) {
        for( int i = 0; i <= ConCmdCount + 1; i++ ) {
            if( cmd == ConCmdList[ i ].name ) {
                CmdFound = true;
                ListPos = i;
                break;
            }
        }
    }
    switch( ListPos ) {
        case 0:
            std::cout<<"Quitting..."<<std::endl;
            RUN = false;
            break;
        case 1:
            std::cout<<"Help requested"<<std::endl;
            break;
        default:
            break;
    }
}
template< class type_All >
int ArraySize( type_All array[] ) {
    return ( sizeof( array ) / sizeof( *array ) );
}
