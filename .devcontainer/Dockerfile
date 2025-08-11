FROM mcr.microsoft.com/devcontainers/base:ubuntu-22.04

RUN <<EOT
cd /tmp
export DEBIAN_FRONTEND=noninteractive
apt-get update
apt-get install -y --no-install-recommends \
    ca-certificates \
    curl \
    gnupg \
    lsb-release \
    software-properties-common
mkdir -p /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | gpg --dearmor -o /etc/apt/keyrings/docker.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" > /etc/apt/sources.list.d/docker.list
apt-get update
apt-get install -y --no-install-recommends \
    build-essential \
    clang \
    clang-format \
    docker-ce-cli \
    docker-compose-plugin \
    less \
    libbsd-dev \
    openssh-client \
    python3-pip \
    tzdata \
    valgrind \
    wget \
    man-db \
    manpages \
    manpages-dev \
    language-pack-ja
pip3 install \
    norminette==3.3.55 \
    c-formatter-42
sed -i "/NotImplementedError/a CLANG_FORMAT_EXEC = \"`which clang-format`\"" \
    "`pip show c-formatter-42 | grep Location | cut -d' ' -f2`/c_formatter_42/formatters/clang_format.py"
update-locale LANG=ja_JP.UTF-8 LC_ALL=ja_JP.UTF-8
ln -sfn /usr/share/zoneinfo/Asia/Tokyo /etc/localtime
update-alternatives --set cc /usr/bin/clang
update-alternatives --set c++ /usr/bin/clang++
wget -q https://raw.github.com/xicodomingues/francinette/master/bin/install.sh
sudo -iu vscode bash /tmp/install.sh
rm install.sh
yes | unminimize
apt-get clean
rm -rf /var/lib/apt/lists/*
EOT

RUN cat <<EOT >> /home/vscode/.zshrc
alias cc='cc -Wall -Wextra -Werror'
alias norm='norminette -R CheckForbiddenSourceHeader'
EOT

RUN install -d -o vscode -g vscode /home/vscode/.vscode-server

ENV LANG=ja_JP.UTF-8
ENV LC_ALL=ja_JP.UTF-8
ENV TZ=Asia/Tokyo
