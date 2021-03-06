#pragma once

#include <Kernel/Net/IPv4Socket.h>

class UDPSocketHandle;

class UDPSocket final : public IPv4Socket {
public:
    static Retained<UDPSocket> create(int protocol);
    virtual ~UDPSocket() override;

    static Lockable<HashMap<word, UDPSocket*>>& sockets_by_port();
    static UDPSocketHandle from_port(word);

private:
    explicit UDPSocket(int protocol);

    virtual int protocol_receive(const ByteBuffer&, void* buffer, size_t buffer_size, int flags, sockaddr* addr, socklen_t* addr_length) override;
    virtual int protocol_send(const void*, int) override;
    virtual KResult protocol_connect(ShouldBlock) override;
    virtual int protocol_allocate_source_port() override;
};

class UDPSocketHandle : public SocketHandle {
public:
    UDPSocketHandle() { }

    UDPSocketHandle(RetainPtr<UDPSocket>&& socket)
        : SocketHandle(move(socket))
    {
    }

    UDPSocketHandle(UDPSocketHandle&& other)
        : SocketHandle(move(other))
    {
    }

    UDPSocketHandle(const UDPSocketHandle&) = delete;
    UDPSocketHandle& operator=(const UDPSocketHandle&) = delete;

    UDPSocket* operator->() { return &socket(); }
    const UDPSocket* operator->() const { return &socket(); }

    UDPSocket& socket() { return static_cast<UDPSocket&>(SocketHandle::socket()); }
    const UDPSocket& socket() const { return static_cast<const UDPSocket&>(SocketHandle::socket()); }
};

