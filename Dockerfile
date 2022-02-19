FROM gcc:latest

WORKDIR /usr/app
COPY ./ .

WORKDIR /usr/app/premake
RUN wget --no-check-certificate https://github.com/premake/premake-core/releases/download/v5.0.0-beta1/premake-5.0.0-beta1-linux.tar.gz && \
 tar xvzf premake-5.0.0-beta1-linux.tar.gz && \
 rm premake-5.0.0-beta1-linux.tar.gz

ENV OLDPATH="${PATH}"
ENV PATH="/usr/app/premake:${OLDPATH}"

WORKDIR /usr/app/sln
RUN premake5 gmake2 && make

CMD /usr/app/Test/build/Debug/Test
