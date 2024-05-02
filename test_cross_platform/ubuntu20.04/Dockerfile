FROM ubuntu:20.04

COPY ../.. ./Project

RUN apt update && \
    apt install -y build-essential && \
    add-apt-repository ppa:ubuntu-toolchain-r/test && \
    apt update && \
    apt install -y g++-10 
    # update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 100 && \
    # update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 100 

CMD ["/bin/bash"]
