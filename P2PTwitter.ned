package oversim.applications.p2ptwitter;

import oversim.common.BaseApp;
import oversim.common.ITier;


simple P2PTwitter extends BaseApp
{
    parameters:
        @class(P2PTwitter);
        bool joinGroups = default(true);
        int messageLength;
        bool sendMessages = default(true);
        
        //goed ge-add vir tcp messages
        int sendPeriod @unit(s);   // how much time to wait between sending packets
        int numToSend;             // how many packets will we send at the same time?
        int largestKey;            // largest key we can pick
        
        //stats collection
        @signal[bytesSentFollow](type="int");
        @statistic[clientBytesSentFollow](title="client follow bytes sent"; source="bytesSentFollow"; record=vector,stats; interpolationmode=none);
        
        @signal[bytesSentReqUsers](type="int");
        @statistic[clientBytesSentReqUsers](title="client user request bytes sent"; source="bytesSentReqUsers"; record=vector,stats; interpolationmode=none);
        
        @signal[bytesRecReqUsers](type="int");
        @statistic[clientBytesRecReqUsers](title="client user request bytes received"; source="bytesRecReqUsers"; record=vector,stats; interpolationmode=none);
        
        @signal[bytesSentJoin](type="int");
        @statistic[clientBytesSentJoin](title="client join bytes sent"; source="bytesSentJoin"; record=vector,stats; interpolationmode=none);
        
        @signal[bytesRecJoin](type="int");
        @statistic[clientBytesRecJoin](title="client join bytes received"; source="bytesRecJoin"; record=vector,stats; interpolationmode=none);
        
        @signal[bytesSentTweet](type="int");
        @statistic[clientBytesSentTweet](title="client tweet bytes sent"; source="bytesSentTweet"; record=vector,stats; interpolationmode=none);
        
        @signal[bytesRecTweet](type="int");
        @statistic[clientBytesRecTweet](title="client tweet bytes received"; source="bytesRecTweet"; record=vector,stats; interpolationmode=none);
}

module P2PTwitterModule like ITier
{
    gates:
        input udpIn;
        input from_lowerTier;
        input from_upperTier;
        input tcpIn;  
        output tcpOut;
        output udpOut;
        output to_lowerTier;
        output to_upperTier;
        
        //ge-add vir tcp
        input trace_in;          // gate for trace file commands

    submodules:
        p2pTwitter: P2PTwitter;
    connections allowunconnected:
        from_lowerTier --> p2pTwitter.from_lowerTier;
        to_lowerTier <-- p2pTwitter.to_lowerTier;
        from_upperTier --> p2pTwitter.from_upperTier;
        to_upperTier <-- p2pTwitter.to_upperTier;
        udpIn --> p2pTwitter.udpIn;
        udpOut <-- p2pTwitter.udpOut;
        
        //ge-add vir tcp
        tcpIn --> p2pTwitter.tcpIn;
        tcpOut <-- p2pTwitter.tcpOut;
        trace_in --> p2pTwitter.trace_in;

}

