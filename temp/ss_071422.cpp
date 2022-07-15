#include<iostream>
#include<string>

#define SS_NONE 0
#define SS_STR 1
#define SS_INT 2

void Parse( std::string cmd );
template< class type_All >
int ArraySize( type_All array[] );
void EmitError( std::string error );
void EmitErrorFatal( std::string error, int errorc );

bool RUN;

typedef struct ConCmd_s { // console command
    std::string name; // command name
    int argt; // argument type [ SS_NONE, SS_STR, SS_INT ]
    int argc; // argument count
    std::string arg[ 4 ]; // argument list
    std::string helpstring; // command help text
} ConCmd;

typedef struct Prgm_s { // program
    std::string name; // program string name
    std::string cmdname; // program cmd name
    int argt; // argument type [ SS_NONE, SS_STR, SS_INT ]
    int argc; // argument count
    std::string arg[ 4 ]; // argument list
    std::string infostring; // program info string
} Prgm;

ConCmd ConCmdList[ 2 ] = {
    ConCmd{ "quit", SS_NONE, 0, "", "Quit the program" },
    ConCmd{ "help", SS_NONE, 0, "", "See a list of commands or specific help for certain commands" }
};

Prgm PrgmList[ 2 ] = {
    Prgm{ "Calculator", "calculator", SS_STR, 4, { "", "", "", "" }, "Standard implementation of a calculator"  },
    Prgm{ "DEBUGTEST", "test", SS_NONE, 0, "", "DEBUG TEST" }
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
    int ListCheck = -1; // 0 = console command, 1 = program command
    if( !CmdFound ) {
        for( int i = 0; i <= ConCmdCount + 1; i++ ) {
            if( cmd == ConCmdList[ i ].name ) {
                CmdFound = true;
                ListPos = i;
                ListCheck = 0;
                break;
            }
        }
    }
    if( !CmdFound ) { // this is retarded but it nulls the rechecking even if a system command was found
        for( int i = 0; i <= PrgmListCount + 1; i++ ) {
            if( cmd == PrgmList[ i ].cmdname ) {
                CmdFound = true;
                ListPos = i;
                ListCheck = 1;
                break;
            }
        }
    }
    if( ListCheck == 0 ) {
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
    } else if( ListCheck == 1 ) {
        switch( ListPos ) {
            case 0:
                std::cout<<"Calculator opened"<<std::endl;
                break;
            case 1:
                std::cout<<"DEBUGTEST"<<std::endl;
                break;
            default:
                break;
        }
    } else {
        EmitError( "Invalid command type recieved." );
        return;
    }
}
template< class type_All >
int ArraySize( type_All array[] ) {
    return ( sizeof( array ) / sizeof( *array ) );
}
void EmitError( std::string error ) {
    std::cout<<std::endl;
    std::cout<<"Error: "<<error<<std::endl;
}
void EmitErrorFatal( std::string error, int errorc ) {
    std::cout<<std::endl;
    std::cout<<"Fatal error: "<<error<<std::endl;
    std::cout<<"System has paused. We are hanging here";
    std::exit( errorc );
}
