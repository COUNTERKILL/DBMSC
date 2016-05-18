#pragma once

class CPacket
{
public:
                    CPacket             (std::size_t src,
                                            std::size_t dst,
                                            std::size_t width, std::size_t length
                                        ):
                                            m_width(width), 
                                            m_length(length)                    {};
                    ~CPacket            ()                                      = default;
public:
                    CPacket             (CPacket&)                              = default;
                    CPacket             (CPacket&&)                             = default;
public:
                    CPacket& operator=  (CPacket&)                              = default;
                    CPacket& operator=  (CPacket&&)                             = default;
public:
    std::size_t     GetWidth            ()                                      { return m_width; };
    std::size_t     GetLength           ()                                      { return m_length; };
private:
    std::size_t     m_width             = 0;
    std::size_t     m_length            = 0;
    std::size_t     m_src               = 0;
    std::size_t     m_dst               = 0;
}