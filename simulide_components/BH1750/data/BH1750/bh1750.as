IoPin@ sdaPin = component.getPin("SDA");
IoPin@ sclPin = component.getPin("SCL");

uint m_lux = 350;
uint m_raw = 420;
uint m_clocks = 0;
bool m_lastScl = true;
bool m_lastSda = true;

void setup()
{
    twi.setAddress( 0x23 );
}

void reset()
{
    sdaPin.setPinMode( 2 );
    sclPin.setPinMode( 2 );
    twi.setMode( 2 );

    sdaPin.changeCallBack( element, true );
    sclPin.changeCallBack( element, true );

    m_clocks = 0;
    m_lastScl = true;
    m_lastSda = true;
    m_raw = m_lux * 12 / 10;
}

void voltChanged()
{
    bool scl = sclPin.getInpState();
    bool sda = sdaPin.getInpState();

    if( scl && m_lastScl && m_lastSda && !sda )
    {
        m_clocks = 0;
        twi.sendByte( uint8( m_raw >> 8 ) );
    }
    else if( scl && !m_lastScl )
    {
        m_clocks++;
        if( m_clocks == 18 ) twi.sendByte( uint8( m_raw & 0xFF ) );
    }
    m_lastScl = scl;
    m_lastSda = sda;
}

void byteReceived( uint d )
{
    print("BH1750 command: " + d );
}

void setLux( uint lux )
{
    if( lux > 54612 ) lux = 54612;
    m_lux = lux;
    m_raw = m_lux * 12 / 10;
}

uint getLux()
{
    return m_lux;
}
