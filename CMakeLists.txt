project(my_ftp)

set(sources main.c include/my_ftp.h main_server/main_server.c communication/socket.c client_server/client_server.c client_server/custom_split.c client_server/str_replace.c client_server/read_and_interpret.c client_server/key_fct/quit.c client_server/key_fct/user.c client_server/key_fct/pass.c client_server/key_fct/cwd.c client_server/key_fct/pwd.c client_server/key_fct/list.c client_server/key_fct/pasv.c client_server/key_fct/help.c client_server/key_fct/cdup.c client_server/key_fct/dele.c client_server/key_fct/noop.c client_server/key_fct/retr.c client_server/key_fct/stor.c client_server/key_fct/port.c communication/communication.c client_server/key_fct/unknown.c)

add_executable(my_ftp ${sources})