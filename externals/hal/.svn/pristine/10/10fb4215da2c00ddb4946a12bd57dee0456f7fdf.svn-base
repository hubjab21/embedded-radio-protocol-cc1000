/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_cli.h
 Author:        Lukasz Krzak
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       Command Line Interface (CLI) module API
--------------------------------------------------------------------------------
 Comments:
================================================================================
 */

#include "hal.h"

// Command prompt
const char CLI_CMD_PROMPT[] = "CMD> ";


extern void CLI_PORT_CursorPosition(IODevice iodevice, int x, int y);
extern void CLI_PORT_SetTopAndBottomMarg(IODevice iodevice, int top, int bottom);
extern void CLI_PORT_EraseDisplay(IODevice iodevice);
extern void CLI_PORT_CursorBackward(IODevice iodevice, int count);


// -----------------------------------------------------------------------------
//  CLI_Create
// -----------------------------------------------------------------------------
CLIConsole CLI_Create(IODevice iodevice) {
    CLIConsole cli;

    cli = (CLIConsole)HEAP_Alloc(sizeof(struct CLIConsoleDesc));
    if (cli) {
        cli->iodevice          = iodevice;
        cli->state.busy        = 0;
        cli->state.multichar   = 0;
        cli->state.doublechar  = 0;
        cli->command_processor = NULL;
        cli->cnt               = 0;
        memset(cli->buf, 0x00, CLI_COMMAND_BUF_SIZE);
    }

    return cli;

} /* CLI_Create */


// -----------------------------------------------------------------------------
//  CLI_Destroy
// -----------------------------------------------------------------------------
void CLI_Destroy(CLIConsole cli) {
    if (cli) {
        HEAP_Free(cli);
    }
} /* CLI_Destroy */


// -----------------------------------------------------------------------------
//  CLI_DisplayMainScreen
// -----------------------------------------------------------------------------
void CLI_DisplayMainScreen(CLIConsole cli) {
    int current_opt = 0;

    DIAG_ASSERT_AND_EXECUTE(DIAG_DEFAULT_CHANNEL, cli) {
        // console object is non-NULL
        DIAG_ASSERT_AND_EXECUTE(DIAG_DEFAULT_CHANNEL, cli->iodevice) {
            // there is an associated iodevice

            // set default cursor position
            CLI_PORT_CursorPosition(cli->iodevice, 1, 1);

            // print out console title
#if defined CLI_CONSOLE_TITLE
            TXTDEV_WriteString(cli->iodevice, CLI_CONSOLE_TITLE);
#endif
            // print option names
#if defined CLI_OPT_0_NAME
            CLI_PORT_CursorPosition(cli->iodevice, CLI_LEFT_MARGIN + CLI_COL_SEPARATION * (current_opt % CLI_NO_OF_COLUMNS), 3 + (current_opt / CLI_NO_OF_COLUMNS));
            TXTDEV_WriteString(cli->iodevice, CLI_OPT_0_NAME);
            current_opt++;
#endif
#if defined CLI_OPT_1_NAME
            CLI_PORT_CursorPosition(cli->iodevice, CLI_LEFT_MARGIN + CLI_COL_SEPARATION * (current_opt % CLI_NO_OF_COLUMNS), 3 + (current_opt / CLI_NO_OF_COLUMNS));
            TXTDEV_WriteString(cli->iodevice, CLI_OPT_1_NAME);
            current_opt++;
#endif
#if defined CLI_OPT_2_NAME
            CLI_PORT_CursorPosition(cli->iodevice, CLI_LEFT_MARGIN + CLI_COL_SEPARATION * (current_opt % CLI_NO_OF_COLUMNS), 3 + (current_opt / CLI_NO_OF_COLUMNS));
            TXTDEV_WriteString(cli->iodevice, CLI_OPT_2_NAME);
            current_opt++;
#endif
#if defined CLI_OPT_3_NAME
            CLI_PORT_CursorPosition(cli->iodevice, CLI_LEFT_MARGIN + CLI_COL_SEPARATION * (current_opt % CLI_NO_OF_COLUMNS), 3 + (current_opt / CLI_NO_OF_COLUMNS));
            TXTDEV_WriteString(cli->iodevice, CLI_OPT_3_NAME);
            current_opt++;
#endif
#if defined CLI_OPT_4_NAME
            CLI_PORT_CursorPosition(cli->iodevice, CLI_LEFT_MARGIN + CLI_COL_SEPARATION * (current_opt % CLI_NO_OF_COLUMNS), 3 + (current_opt / CLI_NO_OF_COLUMNS));
            TXTDEV_WriteString(cli->iodevice, CLI_OPT_4_NAME);
            current_opt++;
#endif
#if defined CLI_OPT_5_NAME
            CLI_PORT_CursorPosition(cli->iodevice, CLI_LEFT_MARGIN + CLI_COL_SEPARATION * (current_opt % CLI_NO_OF_COLUMNS), 3 + (current_opt / CLI_NO_OF_COLUMNS));
            TXTDEV_WriteString(cli->iodevice, CLI_OPT_5_NAME);
            current_opt++;
#endif
#if defined CLI_OPT_6_NAME
            CLI_PORT_CursorPosition(cli->iodevice, CLI_LEFT_MARGIN + CLI_COL_SEPARATION * (current_opt % CLI_NO_OF_COLUMNS), 3 + (current_opt / CLI_NO_OF_COLUMNS));
            TXTDEV_WriteString(cli->iodevice, CLI_OPT_6_NAME);
            current_opt++;
#endif
#if defined CLI_OPT_7_NAME
            CLI_PORT_CursorPosition(cli->iodevice, CLI_LEFT_MARGIN + CLI_COL_SEPARATION * (current_opt % CLI_NO_OF_COLUMNS), 3 + (current_opt / CLI_NO_OF_COLUMNS));
            TXTDEV_WriteString(cli->iodevice, CLI_OPT_7_NAME);
            current_opt++;
#endif
            CLI_PORT_CursorPosition(cli->iodevice, 1, 4 + (current_opt / CLI_NO_OF_COLUMNS));
            IODEV_Write(cli->iodevice, "---", 3, 0);
            CLI_PORT_SetTopAndBottomMarg(cli->iodevice, 5 + (current_opt / CLI_NO_OF_COLUMNS), 23);
            CLI_PORT_CursorPosition(cli->iodevice, 1, 5 + (current_opt / CLI_NO_OF_COLUMNS));
        }
    }

} /* CLI_DisplayMainScreen */


// -----------------------------------------------------------------------------
//  CLI_ProcessConsole
// -----------------------------------------------------------------------------
CLIConsoleAction CLI_ProcessConsole(CLIConsole cli) {
    uint8_t rx_byte;

    DIAG_ASSERT_AND_EXECUTE(DIAG_DEFAULT_CHANNEL, cli) {
        // console object is non-NULL
        DIAG_ASSERT_AND_EXECUTE(DIAG_DEFAULT_CHANNEL, cli->iodevice) {
            // there is an associated iodevice

            // check receiver for incoming data
            if ((IODEV_GetReadCount(cli->iodevice)) && (IODEV_Read(cli->iodevice, &rx_byte, 1, 0))) {
                // a single character has been received
                // first check if the console is busy
                if (cli->state.busy) {
                    // console is busy, exit
                    return CLI_BUSY;
                }

                // test if console mode change character was pressed
                if ('`' == rx_byte) {
                    // change console work mode
                    if (0 == cli->state.multichar) {
                        // enter command mode
                        cli->state.multichar = 1;
                        // reset buffer
                        cli->cnt    = 0x00;
                        cli->buf[0] = 0x00;
                        // display command prompt
                        if (0 == IODEV_Lock(cli->iodevice, 1000)) {
                            TXTDEV_WriteString(cli->iodevice, CLI_CMD_PROMPT);
                            IODEV_Unlock(cli->iodevice);
                        }
                    } else {
                        // enter single character mode
                        cli->state.multichar = 0;
                        TXTDEV_WriteNL(cli->iodevice);
                    }
                    // that's it for now
                    return CLI_NO_ACTION;

                } // if ('`' == rx_byte)

                if (0 == cli->state.multichar) {
                    // single character mode

                    // process key according to the option definitions
                    switch (rx_byte) {
                        case ' ':
                            // default option - refresh screen
                            if (0 == IODEV_Lock(cli->iodevice, 1000)) {
                                CLI_PORT_EraseDisplay(cli->iodevice);
                                CLI_DisplayMainScreen(cli);
                                IODEV_Unlock(cli->iodevice);
                            }
                            break;
#ifdef CLI_OPT_0_KEY
                        case CLI_OPT_0_KEY:
                            CLI_OPT_0_PROC(cli);
                            return CLI_USER_ACTION;
                            break;
#endif
#ifdef CLI_OPT_1_KEY
                        case CLI_OPT_1_KEY:
                            CLI_OPT_1_PROC(cli);
                            return CLI_USER_ACTION;
                            break;
#endif
#ifdef CLI_OPT_2_KEY
                        case CLI_OPT_2_KEY:
                            CLI_OPT_2_PROC(cli);
                            return CLI_USER_ACTION;
                            break;
#endif
#ifdef CLI_OPT_3_KEY
                        case CLI_OPT_3_KEY:
                            CLI_OPT_3_PROC(cli);
                            return CLI_USER_ACTION;
                            break;
#endif
#ifdef CLI_OPT_4_KEY
                        case CLI_OPT_4_KEY:
                            CLI_OPT_4_PROC(cli);
                            return CLI_USER_ACTION;
                            break;
#endif
#ifdef CLI_OPT_5_KEY
                        case CLI_OPT_5_KEY:
                            CLI_OPT_5_PROC(cli);
                            return CLI_USER_ACTION;
                            break;
#endif
#ifdef CLI_OPT_6_KEY
                        case CLI_OPT_6_KEY:
                            CLI_OPT_6_PROC(cli);
                            return CLI_USER_ACTION;
                            break;
#endif
#ifdef CLI_OPT_7_KEY
                        case CLI_OPT_7_KEY:
                            CLI_OPT_7_PROC(cli);
                            return CLI_USER_ACTION;
                            break;
#endif
                        default:
                            // unhandled key - no action
                            return CLI_NO_ACTION;
                    } // switch (rx_byte)
                } else {
                    // multiple character mode
                    if (cli->state.doublechar != 0) {
                        cli->state.doublechar = 0;
                    } else {
                        switch (rx_byte) {
                            case '\n':
                            case '\r':
                                // ENTER
                                if (cli->cnt) {
                                    // attach trailing zero
                                    cli->buf[cli->cnt] = 0x00;
                                    // run external command processor
                                    cli->command_processor(cli);
                                    // clear command buffer
                                    cli->cnt           = 0x00;
                                    cli->buf[cli->cnt] = 0x00;
                                    if (cli->state.busy) {
                                        return CLI_BUSY;
                                    } else {
                                        // display prompt to indicate, that another command can be processed
                                        if (0 == IODEV_Lock(cli->iodevice, 1000)) {
                                            TXTDEV_WriteString(cli->iodevice, CLI_CMD_PROMPT);
                                            IODEV_Unlock(cli->iodevice);
                                        }
                                        return CLI_USER_ACTION;
                                    }
                                }
                                break;
                            case 8:
                                // BACKSPACE
                                if (cli->cnt) {
                                    cli->buf[cli->cnt--] = 0x00;
                                    cli->buf[cli->cnt]   = 0x00;
                                    if (0 == IODEV_Lock(cli->iodevice, 1000)) {
                                        CLI_PORT_CursorBackward(cli->iodevice, 1);
                                        IODEV_Write(cli->iodevice, " ", 1, 0);
                                        CLI_PORT_CursorBackward(cli->iodevice, 1);
                                        IODEV_Unlock(cli->iodevice);
                                    }
                                }
                                break;
                            case 27:
                                // ESC
                                // clear command buffer
                                cli->cnt           = 0x00;
                                cli->buf[cli->cnt] = 0x00;
                                if (0 == IODEV_Lock(cli->iodevice, 1000)) {
                                    TXTDEV_WriteNL(cli->iodevice);
                                    // display prompt to indicate, that another command can be processed
                                    TXTDEV_WriteString(cli->iodevice, CLI_CMD_PROMPT);
                                    IODEV_Unlock(cli->iodevice);
                                }
                                break;
                            case 224:
                                // first symbol of arrow character
                                cli->state.doublechar = 1;
                                break;
                            default:
                                // normal character
                                cli->buf[cli->cnt] = rx_byte;
                                IODEV_Write(cli->iodevice, cli->buf + cli->cnt, 1, 0);
                                cli->cnt++;
                                break;
                        } // switch (rx_byte)
                    }     // if
                }
            } // if data received
        }     // assert (cli->iodevice)
    }         // assert (cli)

    return CLI_NO_ACTION;

} /* CLI_ProcessConsole */


// -----------------------------------------------------------------------------
//  CLI_SetExternalCommandProcessor
// -----------------------------------------------------------------------------
void CLI_SetExternalCommandProcessor(CLIConsole cli, void (*cmd_proc)(CLIConsole cli)) {
    cli->command_processor = cmd_proc;

} /* CLI_SetExternalCommandProcessor */


// -----------------------------------------------------------------------------
//  CLI_ForceCommandMode
// -----------------------------------------------------------------------------
void CLI_ForceCommandMode(CLIConsole cli) {
    // enter command mode
    cli->state.multichar = 1;
    // clear buffer
    cli->cnt    = 0x00;
    cli->buf[0] = 0x00;
    // display command prompt
    if (0 == IODEV_Lock(cli->iodevice, 1000)) {
        TXTDEV_WriteNL(cli->iodevice);
        // display prompt to indicate, that another command can be processed
        TXTDEV_WriteString(cli->iodevice, CLI_CMD_PROMPT);
        IODEV_Unlock(cli->iodevice);
    }
} /* CLI_ForceCommandMode */


// -----------------------------------------------------------------------------
//  CLI_GetCommand
// -----------------------------------------------------------------------------
void CLI_GetCommand(CLIConsole cli, char* dst) {
    size_t i = 0;

    // trailing spaces are already removed from cli->buf

    // just copy first word to the destination buffer
    while ((cli->buf[i] != ' ') && (cli->buf[i] != 0x00) && (cli->buf[i] != '\r') && (cli->buf[i] != '\n')) {
        dst[i] = cli->buf[i];
        i++;
    }

    // add string ending
    dst[i] = 0x00;

    if (cli->buf[i] != 0x00) {
        // last character is non-zero, there is something more on the command line
        cli->offset = i + 1;
    } else {
        // there was just the command
        cli->offset = i;
    }

} /* CLI_GetCommand */


// -----------------------------------------------------------------------------
//  CLI_IsNextArg
// -----------------------------------------------------------------------------
int CLI_IsNextArg(CLIConsole cli) {
    if (cli->buf[cli->offset] != 0x00) {
        return 1;
    }
    return 0;

} /* CLI_IsNextArg */


// -----------------------------------------------------------------------------
//  CLI_GetNextArg
// -----------------------------------------------------------------------------
void CLI_GetNextArg(CLIConsole cli, char* arg) {
    size_t i = 0;

    if (cli->buf[cli->offset] == '"') {
        cli->offset++;
        while ((cli->buf[i + cli->offset] != '"') && (cli->buf[i + cli->offset] != 0x00)) {
            arg[i] = cli->buf[i + cli->offset];
            i++;
        }
        if (cli->buf[i + cli->offset] == '"') {
            cli->offset++;
        }
    } else {
        while ((cli->buf[i + cli->offset] != ' ') && (cli->buf[i + cli->offset] != 0x00)) {
            arg[i] = cli->buf[i + cli->offset];
            i++;
        }
    }
    arg[i] = 0x00;

    if (cli->buf[i + cli->offset] != 0x00) {
        cli->offset += i + 1;
    } else {
        cli->offset += i;
    }
} /* CLI_GetNextArg */


// -----------------------------------------------------------------------------
//  CLI_GetNextArgInt32
// -----------------------------------------------------------------------------
int CLI_GetNextArgInt32(CLIConsole cli, int32_t* arg) {
    size_t i = 0;
    if (cli->buf[cli->offset] == 0) {
        *arg = 0;
        return 3;
    }
    // sprawdzamy, czy uzytkownik nie podal danych w formacie HEX, czyli 0x...
    if ((cli->buf[cli->offset] == '0') && ((cli->buf[cli->offset + 1] == 'x') || (cli->buf[cli->offset + 1] == 'X'))) {
        i += 2;
        uint32_t value_int = 0;
        uint8_t  counter   = 8;
        char*    buffer    = (char*)&cli->buf[i + cli->offset];

        // pierwsza petla w ktorej sprawdzamy, czy aktualnie analizowany znak
        // nie jest spacja, zerem lub czy analizowana liczba znakow nie jest
        // wieksza od 8 (int ma maksymalnie 8 znakow w zapisie szesnastkowym)
        while ((*buffer != ' ') && (*buffer != 0x00) && counter) {
            // sprawdzenie, czy podany znak jest dozwolonym znakiem
            // przy tym formacie wprowadzania liczby
            if ((*buffer < '0' || *buffer > '9') && (*buffer < 'A' || *buffer > 'F') && (*buffer < 'a' || *buffer > 'f')) {
                // przeskoczenie za pomoca ponizszej petli na koniec analizowanego ciagu znakow
                while ((cli->buf[i + cli->offset] != ' ') && (cli->buf[i + cli->offset] != 0x00)) {
                    i++;
                }
                if (cli->buf[i + cli->offset] != 0x00) {
                    cli->offset += i + 1;
                } else {
                    cli->offset += i;
                }
                // invalid character
                return 1;
            }
            value_int <<= 4;
            if (*buffer >= 0x30 && *buffer <= 0x39) {
                value_int += (uint32_t)(*buffer & 0xf);
            } else {
                value_int += (uint32_t)((*buffer & 0xf) + 9);
            }
            i++;
            counter--;
            buffer = (char*)&cli->buf[i + cli->offset];
        }
        // sprawdzenie, czy w buforze nie ma jeszcze jakis znakow
        if ((cli->buf[i + cli->offset] != ' ') && (cli->buf[i + cli->offset] != 0x00)) {
            // przeskoczenie za pomoca ponizszej petli na koniec analizowanego ciagu znakow
            while ((cli->buf[i + cli->offset] != ' ') && (cli->buf[i + cli->offset] != 0x00)) {
                i++;
            }
            if (cli->buf[i + cli->offset] != 0x00) {
                cli->offset += i + 1;
            } else {
                cli->offset += i;
            }
            // integer out of range
            return 2;
        }
        *arg = value_int;
        return (0);
    }
    // tryb zwykly
    else {
        int32_t  value_arg            = 0;
        uint32_t fractional_nominal   = 0;
        uint32_t fractional_denominal = 1;
        uint8_t  prefix               = 0;
        uint8_t  counter              = 10;
        uint8_t  minus                = 0;

        // pierwsza petla w ktorej sprawdzamy, czy aktualnie analizowany znak
        // nie jest spacja, zerem lub czy analizowana liczba znakow nie jest
        // wieksza od 10 (int ma maksymalnie 10 znakow w zapisie dziesietnym)
        //
        // wewnatrz tej petli analizujemy calkowita czesc skanowanej liczby
        while ((cli->buf[i + cli->offset] != ' ') && (cli->buf[i + cli->offset] != 0x00) && counter) {
            // zaczynamy analize ciagu znakow - sprawdzamy, czy analizowany
            // znak nie jest minusem
            if (counter == 10) {
                if (cli->buf[i + cli->offset] == '-') {
                    minus = 1;
                    i++;
                    continue;
                }
            }
            // sprawdzamy, czy analizowany znak nie jest kropka
            // jezeli tak, to przehodzimy do drugiej petli w ktorej
            // bedziemy analizowac czesc ulamkowa
            if (cli->buf[i + cli->offset] == ',' || cli->buf[i + cli->offset] == '.') {
                counter = 10;
                i++;
                break;
            }
            // sprawdzamy, czy analizowany znak nie jest jednym ze standardowo
            // uzywanych przedrostkow ukladu SI
            if (cli->buf[i + cli->offset] == 'G' || cli->buf[i + cli->offset] == 'M' || cli->buf[i + cli->offset] == 'k') {
                prefix  = cli->buf[i + cli->offset];
                counter = 10;
                i++;
                break;
            }
            // wszystkie znaki inne niz cyfry, akceptowalne przy analizowaniu liczb
            // zostaly juz sprawdzone w poprzednich liniach - teraz sprawdzamy tylko
            // czy analizowany znak jest cyfra czy nie
            if (cli->buf[i + cli->offset] < 0x30 || cli->buf[i + cli->offset] > 0x39) {
                // przeskoczenie za pomoca ponizszej petli na koniec analizowanego ciagu znakow
                while ((cli->buf[i + cli->offset] != ' ') && (cli->buf[i + cli->offset] != 0x00)) {
                    i++;
                }
                if (cli->buf[i + cli->offset] != 0x00) {
                    cli->offset += i + 1;
                } else {
                    cli->offset += i;
                }
                // invalid character
                return 1;
            }
            // sprawdzamy, czy miescimy sie jeszcze w zakresie zmiennej typu int
            if (counter == 1) {
                if (value_arg >= 214748364 && cli->buf[i + cli->offset] > 0x37) {
                    // przeskoczenie za pomoca ponizszej petli na koniec analizowanego ciagu znakow
                    while ((cli->buf[i + cli->offset] != ' ') && (cli->buf[i + cli->offset] != 0x00)) {
                        i++;
                    }
                    if (cli->buf[i + cli->offset] != 0x00) {
                        cli->offset += i + 1;
                    } else {
                        cli->offset += i;
                    }
                    // integer out of range
                    return 2;
                }
            }
            value_arg *= 10;
            value_arg += (int32_t)(cli->buf[i + cli->offset] & 0xf);
            counter--;
            i++;
        }

        // druga petla w ktorej sprawdzamy, czy aktualnie analizowany znak
        // nie jest spacja, zerem lub czy analizowana liczba znakow nie jest
        // wieksza od 10 (int ma maksymalnie 10 znakow w zapisie dziesietnym)
        //
        // wewnatrz tej petli analizujemy ulamkowa czesc skanowanej liczby
        while ((cli->buf[i + cli->offset] != ' ') && (cli->buf[i + cli->offset] != 0x00) && counter) {
            // sprawdzamy, czy analizowany znak nie jest jednym ze standardowo
            // uzywanych przedrostkow ukladu SI
            if (cli->buf[i + cli->offset] == 'G' || cli->buf[i + cli->offset] == 'M' || cli->buf[i + cli->offset] == 'k') {
                prefix = cli->buf[i + cli->offset];
                i++;
                break;
            }
            // wszystkie znaki inne niz cyfry, akceptowalne przy analizowaniu liczb
            // zostaly juz sprawdzone w poprzednich liniach - teraz sprawdzamy tylko
            // czy analizowany znak jest cyfra czy nie
            if (cli->buf[i + cli->offset] < 0x30 || cli->buf[i + cli->offset] > 0x39) {
                // przeskoczenie za pomoca ponizszej petli na koniec analizowanego ciagu znakow
                while ((cli->buf[i + cli->offset] != ' ') && (cli->buf[i + cli->offset] != 0x00)) {
                    i++;
                }
                if (cli->buf[i + cli->offset] != 0x00) {
                    cli->offset += i + 1;
                } else {
                    cli->offset += i;
                }
                // invalid character
                return 1;
            }
            // sprawdzamy, czy miescimy sie jeszcze w zakresie zmiennej typu unsigned int
            if (counter == 1) {
                if (fractional_nominal >= 429496729 && cli->buf[i + cli->offset] > 0x35) {
                    // przeskoczenie za pomoca ponizszej petli na koniec analizowanego ciagu znakow
                    while ((cli->buf[i + cli->offset] != ' ') && (cli->buf[i + cli->offset] != 0x00)) {
                        i++;
                    }
                    if (cli->buf[i + cli->offset] != 0x00) {
                        cli->offset += i + 1;
                    } else {
                        cli->offset += i;
                    }
                    // integer out of range
                    return 2;
                }
            }
            fractional_nominal *= 10;
            fractional_nominal += (uint32_t)(cli->buf[i + cli->offset] & 0xf);
            i++;
            counter--;
            fractional_denominal *= 10;
        }

        if ((cli->buf[i + cli->offset] != ' ') && (cli->buf[i + cli->offset] != 0x00)) {
            // przeskoczenie za pomoca ponizszej petli na koniec analizowanego ciagu znakow
            while ((cli->buf[i + cli->offset] != ' ') && (cli->buf[i + cli->offset] != 0x00)) {
                i++;
            }
            if (cli->buf[i + cli->offset] != 0x00) {
                cli->offset += i + 1;
            } else {
                cli->offset += i;
            }
            // integer out of range
            return 2;
        }
        // uwzglednienie przedrostkow
        if (prefix == 'k') {
            value_arg *= 1000;
            if (fractional_nominal) {
                // ten switch sluzy do sprawdzenia, jak duza wartosc znajduje sie po przecinku
                // (wartosc po przecinku jest liczba unsigned int)
                // to sprawdzanie i rozne w zaleznosci od wielkosci danych przetwarzanie
                // liczby po przecinku jest konieczne w celu mieszczenia sie w zakresie
                // zmiennej 32-bitowej (np nie mozemy wartosci 1000000 pomnozyc przez 1000000
                // gdyz nie zmiesci sie to w int)
                switch (fractional_denominal) {
                    case 10000000: value_arg += fractional_nominal / 10000; break;
                    case 100000000: value_arg += fractional_nominal / 100000; break;
                    case 1000000000: value_arg += fractional_nominal / 1000000; break;
                    default:
                        fractional_nominal *= 1000;
                        value_arg += fractional_nominal / fractional_denominal;
                        break;
                }
            }
        } else if (prefix == 'M') {
            value_arg *= 1000000;
            if (fractional_nominal) {
                // ten switch sluzy do sprawdzenia, jak duza wartosc znajduje sie po przecinku
                // (wartosc po przecinku jest liczba unsigned int)
                // to sprawdzanie i rozne w zaleznosci od wielkosci danych przetwarzanie
                // liczby po przecinku jest konieczne w celu mieszczenia sie w zakresie
                // zmiennej 32-bitowej (np nie mozemy wartosci 1000000 pomnozyc przez 1000000
                // gdyz nie zmiesci sie to w int)
                switch (fractional_denominal) {
                    case 10000:
                        fractional_nominal *= 100;
                        value_arg += fractional_nominal;
                        break;
                    case 100000:
                        fractional_nominal *= 10;
                        value_arg += fractional_nominal;
                        break;
                    case 1000000: value_arg += fractional_nominal; break;
                    case 10000000: value_arg += fractional_nominal / 10; break;
                    case 100000000: value_arg += fractional_nominal / 100; break;
                    case 1000000000: value_arg += fractional_nominal / 1000; break;
                    default:
                        fractional_nominal *= 1000000;
                        value_arg += fractional_nominal / fractional_denominal;
                        break;
                }
            }
        } else if (prefix == 'G') {
            value_arg *= 1000000000;
            if (fractional_nominal) {
                // ten switch sluzy do sprawdzenia, jak duza wartosc znajduje sie po przecinku
                // (wartosc po przecinku jest liczba unsigned int)
                // to sprawdzanie i rozne w zaleznosci od wielkosci danych przetwarzanie
                // liczby po przecinku jest konieczne w celu mieszczenia sie w zakresie
                // zmiennej 32-bitowej (np nie mozemy wartosci 1000000 pomnozyc przez 1000000
                // gdyz nie zmiesci sie to w int)
                switch (fractional_denominal) {
                    case 10:
                        fractional_nominal *= 100000000;
                        value_arg += fractional_nominal;
                        break;
                    case 100:
                        fractional_nominal *= 10000000;
                        value_arg += fractional_nominal;
                        break;
                    case 1000:
                        fractional_nominal *= 1000000;
                        value_arg += fractional_nominal;
                        break;
                    case 10000:
                        fractional_nominal *= 100000;
                        value_arg += fractional_nominal;
                        break;
                    case 100000:
                        fractional_nominal *= 10000;
                        value_arg += fractional_nominal;
                        break;
                    case 1000000:
                        fractional_nominal *= 1000;
                        value_arg += fractional_nominal;
                        break;
                    case 10000000:
                        fractional_nominal *= 100;
                        value_arg += fractional_nominal;
                        break;
                    case 100000000:
                        fractional_nominal *= 10;
                        value_arg += fractional_nominal;
                        break;
                    case 1000000000: value_arg += fractional_nominal; break;
                    default:
                        fractional_nominal *= 1000000000;
                        value_arg += fractional_nominal / fractional_denominal;
                        break;
                }
            }
        }
        if (minus) {
            *arg = -value_arg;
        } else {
            *arg = value_arg;
        }


        if (cli->buf[i + cli->offset] != 0x00) {
            cli->offset += i + 1;
        } else {
            cli->offset += i;
        }

        return (0);
    }

} /* CLI_GetNextArgInt */


// -----------------------------------------------------------------------------
//  CLI_GetBack
// -----------------------------------------------------------------------------
void CLI_GetBack(CLIConsole cli, int argc) {
    uint32_t i;

    if (!cli->buf[cli->offset]) {
        i = 1;
    } else {
        i = 2;
    }

    while ((argc > 0) && (cli->offset > i)) {
        while ((cli->buf[cli->offset - i] != ' ') && (cli->offset > i)) {
            i++;
        }
        argc--;
    }

    cli->offset -= i - 1;

} /* CLI_GetBack */
