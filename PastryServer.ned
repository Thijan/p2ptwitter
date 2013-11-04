//
// Copyright (C) 2009 Institut fuer Telematik, Universitaet Karlsruhe (TH)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

//
// @author Antonio Zea
//

import oversim.common.BaseApp;
import oversim.common.ITier;

package oversim.applications.p2ptwitter;

simple PastryServer extends BaseApp
{
    parameters:
        @class(PastryServer);
        int sendPeriod @unit(s);   // how much time to wait between sending packets
        int numToSend;             // how many packets will we send at the same time?
        int largestKey;            // largest key we can pick
        
        //stats collection           
        @signal[bytesRecFollow](type="int");
        @statistic[servBytesRecFollow](title="Server follow bytes received"; source="bytesRecFollow"; record=vector,stats; interpolationmode=none);
        
        @signal[bytesSentReqUsers](type="int");
        @statistic[servBytesSentReqUsers](title="Server user request bytes sent"; source="bytesSentReqUsers"; record=vector,stats; interpolationmode=none);
        
        @signal[bytesRecReqUsers](type="int");
        @statistic[servBytesRecReqUsers](title="Server user request bytes received"; source="bytesRecReqUsers"; record=vector,stats; interpolationmode=none);
        
        @signal[bytesSentJoin](type="int");
        @statistic[servBytesSentJoin](title="Server join bytes sent"; source="bytesSentJoin"; record=vector,stats; interpolationmode=none);
        
        @signal[bytesRecJoin](type="int");
        @statistic[servBytesRecJoin](title="Server join bytes received"; source="bytesRecJoin"; record=vector,stats; interpolationmode=none);
        
        @signal[bytesSentTweet](type="int");
        @statistic[servBytesSentTweet](title="Server tweet bytes sent"; source="bytesSentTweet"; record=vector,stats; interpolationmode=none);
        
        @signal[bytesRecTweet](type="int");
        @statistic[servBytesRecTweet](title="Server tweet bytes received"; source="bytesRecTweet"; record=vector,stats; interpolationmode=none);
}

module PastryServerModules like ITier
{
    gates:
        input udpIn;             // gate from the UDP layer
        output udpOut;           // gate to the UDP layer
        input from_lowerTier;    // gate from the lower tier
        input from_upperTier;    // gate from the upper tier
        output to_lowerTier;     // gate to the lower tier
        output to_upperTier;     // gate to the upper tier
        input trace_in;          // gate for trace file commands
        input tcpIn;             // gate from the TCP layer
        output tcpOut;           // gate to the TCP layer

    submodules:
        application: PastryServer;

    connections allowunconnected:
        from_lowerTier --> application.from_lowerTier;
        to_lowerTier <-- application.to_lowerTier;
        udpIn --> application.udpIn;
        udpOut <-- application.udpOut;
        tcpIn --> application.tcpIn;
        tcpOut <-- application.tcpOut;
        trace_in --> application.trace_in;
}
