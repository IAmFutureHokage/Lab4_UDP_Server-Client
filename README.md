# Lab4_UDP_Server-Client

 Для сервера сборки на виндоус gcc -o udpserver cmd/main.c infrastructure/storage.c models/domain.c adapters/udp_windows.c handlers/getip.c config/config.c -I. -lws2_32

 Хандлер неполноценный, потому что роут всего один, для лабораторной домую достаточно 

 Из цикла не выходит, потому что нажатие клавитуары вроде не очень имеет смысл, а если и делать, то для линукс и виндоус по-разному, снова адаптеры городить. Я решил, что для лабораторной это избыточно.

 Сборка клиента на виндоус gcc -o client.exe client.c -lws2_32 -Wall

 Usage: client.exe <domain>