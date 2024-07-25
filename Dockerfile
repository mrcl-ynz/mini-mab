FROM alpine:latest

RUN apk add --no-cache g++

COPY src usr/src/app

WORKDIR /usr/src/app

RUN g++ -o app main.cpp

CMD ["./app"]
