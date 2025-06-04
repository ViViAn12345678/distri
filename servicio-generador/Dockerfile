FROM gcc:latest
RUN apt-get update && apt-get install -y libmicrohttpd-dev
WORKDIR /app
COPY . .
RUN gcc main.c -o generador -lm -lmicrohttpd
CMD ["./generador"]