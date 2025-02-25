#include <sstream>
#include <string>

#include "vtkDearImGuiInjector.h"

#include "vtkActor.h"
#include "vtkCallbackCommand.h"
#include "vtkCameraOrientationWidget.h"
#include "vtkCameraOrientationRepresentation.h"
#include "vtkCameraOrientationWidget.h"
#include "vtkConeSource.h"
#include "vtkInteractorStyle.h"
#include "vtkInteractorStyleSwitch.h"
#include "vtkNew.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include <vtkProperty.h>

#ifdef ADOBE_IMGUI_SPECTRUM
#include "imgui_spectrum.h"
#endif
#include "imgui.h"                 // to draw custom UI
#include "vtkOpenGLRenderWindow.h" // needed to check if opengl is supported.

// Listens to vtkDearImGuiInjector::ImGuiSetupEvent
static void SetupUI(vtkDearImGuiInjector*);
// Listens to vtkDearImGuiInjector::ImGuiDrawEvent
static void DrawUI(vtkDearImGuiInjector*);
static void HelpMarker(const char* desc);

//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
  // Create a renderer, render window, and interactor
  vtkNew<vtkRenderer> renderer;
  vtkNew<vtkRenderWindow> renderWindow;
  vtkNew<vtkRenderWindowInteractor> iren;
  renderWindow->SetMultiSamples(8);
  renderWindow->AddRenderer(renderer);
  iren->SetRenderWindow(renderWindow);

  // Create pipeline
  vtkNew<vtkConeSource> coneSource;
  coneSource->Update();

  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(coneSource->GetOutputPort());

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);
  actor->GetProperty()->SetOpacity(0.3);


  // Add the actors to the scene
  renderer->AddActor(actor);

  // Start rendering app
  renderer->SetBackground(0.2, 0.3, 0.4);
  renderWindow->Render();
  // enable depth peeling
  renderer->SetUseDepthPeeling(1);
  renderer->SetMaximumNumberOfPeels(10);
  renderer->SetOcclusionRatio(0.1);
  renderWindow->SetAlphaBitPlanes(1);
  renderWindow->SetMultiSamples(0);
  // renderer->UseFXAAOn();
  // set gradient color...
  renderer->GradientBackgroundOn();
  renderer->SetBackground(0.6, 0.8, 1.0); // Light sky blue
  renderer->SetBackground2(0.8, 0.9, 1.0); // Darker sky blue

  /// Change to your code begins here. ///
  // Initialize an overlay with DearImgui elements.
  vtkNew<vtkDearImGuiInjector> dearImGuiOverlay;
  // 💉 the overlay.
  dearImGuiOverlay->Inject(iren);
  // These functions add callbacks to ImGuiSetupEvent and ImGuiDrawEvents.
  SetupUI(dearImGuiOverlay);
  // You can draw custom user interface elements using ImGui:: namespace.
  DrawUI(dearImGuiOverlay);
  /// Change to your code ends here. ///

  vtkNew<vtkCameraOrientationWidget> camManipulator;
  camManipulator->SetParentRenderer(renderer);
  camManipulator->AnimateOn();
  camManipulator->SetAnimatorTotalFrames(60);
  camManipulator->On();
  auto rep = vtkCameraOrientationRepresentation::SafeDownCast(camManipulator->GetRepresentation());
  rep->AnchorToLowerRight();

  // Start event loop
  renderWindow->SetSize(1920, 1000);
  vtkInteractorStyleSwitch::SafeDownCast(iren->GetInteractorStyle())->SetCurrentStyleToTrackballCamera();
  // iren->EnableRenderOff();
  iren->Start();

  return 0;
}

//------------------------------------------------------------------------------
// Custom extra bloat to look good and show some VTK information
//------------------------------------------------------------------------------
// File: 'Karla-Regular.ttf' (16848 bytes)
// Exported using binary_to_compressed_c.cpp
#ifndef ADOBE_IMGUI_SPECTRUM
static const char Karla_Regular_compressed_data_base85[15900 + 1] =
  "7])#######5Z9sf'/###I),##bw9hLQXH##j$1S:'>pgLZvaAd668X%QUQl;*31Qg3R9s/N@4',:a`T9n&)Seo$,p8ZW%q/"
  "^6se=K9C[HP>JeE';G##Uu/>8i1i86<CDmLg@AS@'Tx-3"
  "`Nc4qh2TlS^^ppAqV,-GZ6%GT0MXVRk3r]l%J%/"
  "GBgO2(%qY>-B)PY%,5LsC_Ta.SPQ)mfLbFe<b';9Cnfx2aceA&,r1dD4AJr9.s+`G2)a4&>V3dW.;h^`I^bcMU375esm]u."
  "Uo6Q<B"
  "UlLpWTxI/L1#gd<0iR/GTG/"
  "58ID^VIv,i?-qmnUCABcDr1V5lLbQWfq@C=GHX1(%7s;]M)l%1t%1)Q-GN6ArMBMx92MA>>#aEl-$8XW>-jge<6'..w#oZ@"
  "U.&MBeJM_Nj0V'2+8-0KP&"
  "mHe]F4h2W%WgJe$_^.R38^5/v*>uu#?PO;.('I0#RGYn*w*]`X/"
  "n+aXhdWV$6IL^#$,>>#qbjV74iWh#I#g=uTB2L,dA1G`Bf%=(],LF%']T:#(K.+M9+`P/v/HP/nx&58U76:)SW=gG"
  ",Qj)#S^[*N_dq2#?\?`IMRmq@k(NG_&j@ZY#-D-F%31>F%1fN$KuK0A=sbtx+#_t%48S'299'QV6j]HV?r][]+';>J:LX9(,"
  "NJrx4FHcf(jWZY,R>05/a:2F%I;8>5U=<D3KlZc2T3HS7"
  "S=W`3oF=A+Feco7Qg6R*L.c`*oKT]4WH)58C-ux4d82>5i8kl/"
  "]U;D<[5K026g[Y,l3HP8pj0R3#W8JCiw<D3unt.C2;l-$65[w'ZM`w'J::JCmAk-$9+WS%fB/F%,6<JCjoNk+XXYiB"
  "M6i--LG-F%Yp0F%>gv9)WW&29v=$s$a8hu>k`df(_wNM',U&,2TB45&k-B-dB&xE7+$GJ14aD+rO%fc)<H9a40SnQWo-@M9("
  "97JCZEt(3'wX>6%`kA#JA'k.w3X]#^J8r/Xd@H#`:ol#"
  "4'Ff-EvY9V$cm-$oO*:2KJPJ:/mB5KHGUR'.rDSIP=45At?qCscA/"
  "Jh,Cq'##1j:mZJtCjbhfo@jNlEeD$ZEe0bp%4oxDG)*r]`*eY6H*)x=A+apxc3,^2.$Uu._Jfxa-6%ej-$gjd`*"
  "1[3F%Ob_rZ8sk;-cDUxO5FUxOqx1'#IN5/"
  "$P].R3X2cD4'iu8.[gkl&-k@T&.+%]k+L;s%m=9^#&8D#Q^w3CMfhjfL6Ng-#V]0B#3Tu%2Tce@#7.N`#1rm(#KA<jLbd8[#"
  "qW.H#^j(c#"
  "Pb+w$$%HS7tbtx+n7]`*siMW/"
  "F0:*#f####'S5s-nlRfLP:$##27FGMm8#&#kAt$M->`'#R-^g1XqH0#hQD4#+d46#:IQ&MTeM:#MsM<#nu4Y#kT_n#>'^R-;"
  "<o=-gP8wu#&###'oOk1"
  "W1@8#$C0:#BHd;#B(t$OPt7=-KcEX%0.Z7vFUh3v:Q42vlQ`0ve?D0vYqc/vR_G/"
  "vZ)kTu7pC6l?avjkIZqUMAk-gXNq%s$YCN:/&)###^$v=PrwSfLWZaH$=R<T%ME#n&^8`0(n+FI)"
  "(u,c*8hi%,HZO>-XM6W.i@sp/#4Y313'@L2Cp&f3Scc(5dUIA6tH0Z7.<ms8>/"
  "S6:Nx9O;_kvh<o^]+>)QCD?9D*^@I7gvACH4.##K0DImSJZK#O'##/l-UM?_jnNOQG1P`A%/QZZlHQ"
  "+xm-$.%F2CR-(mSeHQJCW3'##SE(##`?_c.:,+rC0MV.GBObcH5SmAJ[[gDSWCc2_Z+Gb[NCf=(K,'##l8q'#,pr4#_9#F#="
  "gkI#HKDO#Ub<T#F#aW#@<X]#as[d#iV4m#^$iv#N)x)$"
  "#>C3$ID]T$C-X=$v=xL$1]4q$$PA]$5g9b$cJ=i$Y0Bm$fCC7%puVw$Efm(%I0K2%@0t9%L[:?%bX8E%ko0J%`0TM%JS4Q%"
  "2U3T%%)$_%iI-g%^tQ4&Q@&&&w$*-&3jIL&f+89&C4s@&"
  "Ab8I&8a5R&T6RW&h'>^&11Nd&[C$0'6[hr&8dw%'?$p*'ng8M''fV<'a16C'I*<h'`i7P'u4mV'/"
  "$,b'8G`k'x1tx'#P0F($*n4(aHJA(m]jP(3T:_(LRbi(nWqr(mbVw(d`(,)sX%5)"
  "9Ge@)oE6K)^pQS)Ym$[)Uti%*hCke)V5,j)*>gq);HLv)Y)YB*cf(0*R$J9*E5u^*M/5##nNJ=#c6:/"
  "#1f1$#mUE%$bwYd3aIcI)>?ex%V''Z-IsC^#7tVP_mfxiLsqJfLMR6##eY3T#"
  "hhLxLUF5gLNIr8.X>l-$R&A<6YBs-$#A3rjQLO_/V1qu,n@)&=^7pu,l>,<.Rk&>.kJ(.$_`%E3WG5s-,O5gLIYqlLi/"
  "LB#==0h:SJJ/C[VS/C&$cNTGSK-D`nq-D>L.h:D#o3TqM,P4"
  "nH4uL0sG:]YIFI]bA'XL4wl@X$9?VdS159/PU$##x^3t_9IE:./[v)4buA(4mCTBfR*i+4BYB+*U(NT/UXxU/w;xF4Uu/"
  "+*2]wC#uxUbGKdc#Jpxs`=*1C'72D**<s7&b@k$bJs&gC_,"
  "(F&f;fVN&=<hb*?DBq/'fJ`e?teB@%p@Du&sr5F,OaDs6Vm,P:-CYvcl#f[$V1B(sC4+/"
  "L?\?(,)[=PV-01ol(ig'u$*W8f3c)qv-iL0+*;UKu.&X'B#O4ji-6BqTVJL,7*fH6R*E*sMq"
  "q&kU:BoC^5T0PD39Wdbu$w@YY&_8I4xK&I4Pp+B,=Z/"
  "a##bvs8AQQW8*6e31++pQ0b@CxOcP_-O9=]U;))B[5)S$##*QCV?,YXJCt=PS.0AR]4*`$s$/0ihL1R/J3,@fBJl%u/"
  "MaYfF4"
  "NECtUjsw<%V61A$0S<+3BgJf35`)K)9i<X(rPH`#B.4q0Y_]U/c#jP8I3MW/6b2qD&C>W'Do@>DWNT'9G,xS:/"
  "R%o_;h-h44#(JDC8*5A8IEN(#.f3:wtd,*q/d;;(^[g<-Qt@I(oxO="
  "HXFrAm)4LdDC<Y7dfwI2D8B*[M),##_8I8#fP(xLrU),)7Rs)Fx,kZ#Z0%(Msk-##R9^M#FA':#>qbf(x?n5/"
  "hRQ65he_P5[$vWB^##YufKaZ?lub3@M),##c&l?-o4&R0s0`a4jj'u$"
  "Lh3>N6l5I#F[/w?krOn?NdTw0F$>D#gKOe#3$M$#?9`a4Fb^=%:d*E**$4Q/t+F+E5/p)E6/"
  "^81H7K_#guxF4;+&G44tAKDrqh-6190I$2u/Poc>,F%bT/i)_kY)49,B+4F)_JfgwCT#"
  "Qdk5h>GJ6aQP[^,j,j4]39bw0b-v>5j%>c4A=MA53#Y$66HWA+4JMq8g$]],W2m92tOH>#K<.29@=%_SP0fX-Y+`ZuI0'"
  "t8B,Zl09NJ=#vB+.#@?$)*Ek/Q/-rgG3<@MW->[Jm/^(E%v"
  "cVah#Nu=d4(bM8.P5r*uM;b9uW7YY#LiA(ssk&/Lk1?m'w=:E5,Zc8/>6S5/vu/"
  "+*)Pn.UArg%NjN.%>HEQh#(t60Y7MtRX+MKIeNnvEMu%iH-023Y..O_/#QF/e%950J3o)ct$&f,03"
  "or9+4GMCN0q]7&+G5>>#d9%##f/a9Dcx###tYW+0OJ,G4RD^+4Koh_%kIuD4aIcI)=C[s$$vTM#(b/"
  "*><-m#B.1v$%e(sPaZ0ppKkS*R:5G$P(5^i#?J#=.3%`r<T5_jL)1We9Mi`)kb"
  "2IpE@HY`$'wPe)*IQ4W-[HG3bs77<.6gE.3RxU_%l=Z[FLC1Bfe`98@EfDe=9cL*>0[3:'W#cu^0ZNEC<Uf_6SHD=BNZcpB;"
  "IarAgs.c==iWHmR/5##?5YY#hwH0#h_kgLT7Rq7n*/^-"
  ":[TD3Od,8FCPeF`CqE2oVD.PA+Wbg6$2r:?PxY$0?Y8&vp1Yu#[`R%#J_a=.1q3-vaK%J37oxv-qVkL)tspTVSQZuY/"
  "%:A#+a%e(eJY'I0,NQ<FqaV7bd+K#]=5-&jTRvBBGs:%P9^C/"
  "XYd$vJ+ffLJa8%#G2o#/1m@d)'Fx;8;>Uv-6:Be?hb@s$k@Vo%>U^:/"
  ">:;n]J>lJCaT8#B$YT(J>9pYu#$;bG<GCfh%sW34fp;fFGZSQ#Q'@Q;iF.]8r09;8)DQ-Zm,Ro#IHY##:XR@#"
  "[W5*nL[W=lg6q^u?,eV:w%C20NK#D/^r2%v&S>LMHO>&#a$(,)%F&T.Ynn8%a[eF%s+-J*cc>D/w7WT/"
  "<3rhLPW$lLIlx^dpp$^MWpk39j&frP7L$N;U%*Q24Wm60I@MI=9Yqr6gPC[@"
  "Y,bF=?TFl9p$CpCfbE4)^IEE63EWn'NH:3(1>UVAD7[Y#lF]9M[aZ9M1rho.f3].3&V'f)hCh8.)NsI3d/ob4?_#V/"
  "BSc)%x_>?IK&xf3#;gX@D0P:28t=j=G0?F-D2#3BBO,#TGr(FG"
  "sg^<1()5rrEd(J>Bh6@52EB)=;8v(?SFSa5U%^HFsh#_#sFAD*8uLf_n_d;-rSl)%(<PF%:x)Z-#%qG39pcG*jY,W-8rHF%"
  "M5YY#EY,SRY`e-6dE(,)He39.j%>c4x(4)FC;(<-@Xos8"
  "_gkA#@Qk0&x+;'#<#mj#fGY##.r-W$TwJu.G+V=lxbR_u'O&a#R6=m6g[7)M^tH+#4wYN#;nHi$L<fX-bXaJ1t]4i^$o1i^&"
  "VNgaY$3wgv$x+2_jjiUCg(2)j6wP/&AgH#V:;Y3$x2ul"
  ":lfJ9:Shff^5R_,5]%>cj2%&+F7$##[3)KavnXI)dI+gL#1ue)C.@x6-l%$$P#MT%1n#W(YS`hbrV2,+[vp*<w93<7.tKv-"
  "BTX>-Y?Hp:Whwg3WJO**K@JU/e?=B6$7K_unr6@-ml+jL"
  "vtqh.`[(($a)c(.B+vlL0Ua=.Yj,N0dYEF3NP,G45>PjLlT]s$<W/i)d+39/x/"
  "X,3UGK-QhEj;-en7T%*<gF4_R(f)0[.&6?:Ai3c5SK)6,T-WbC>:2A3d^hp'?<8-aemPB75h>5ONv#"
  "9hoj:ILpD64;=&>>P2`553*I3J=iVAGF%22mdsa_M_>uRrj](7#>l^8%Lcv-A.DRBL_E=:Tt:g%rr###mlPVH4=35&jc;"
  "F3N`?<.cP/J3MbXsg2?r[4OFP^D$fBxODM)V#]>uu#3T&##"
  "UXn92o)[`*MUWq22Y2K)3hD784>g;.I)2hl9P]L(XRq^oF@vMCoA:+6S+YEGc[jMo0$?<8.p889?7+k#u*kH43q5B=YV4n'"
  "XQIL2HxOD*NN$)#WH9D3QTPA4gm()*d`G-3(@n5/?;Rv$"
  "wR`3=lcsI30Zc8/T[587q#W@>kF=J<9XR5;CLC_o#'+/"
  "L&@[w5hAFsP6WTEH[6hBYrBU&#.<^;-Sl'S-*')x.*Ep;.F(bT^N(r;.&4_.ZgNxW<Fd.?Kn=SVH[(Z7Z5-Cpfep/1Oqx8;-"
  "^U<^-#((F7hMi^oX)XbNgt#I#tQ3T#$i,V#+(*h#IIqg8.Tbg$WT&##e5u92ZxV:2=gtMCtThLg$:J7nB<_<.sSkUmo1#Fn]"
  "_biK<o###o4+R-PdD^N%3i*4o;oO(]&Bg0/k:`KQjQK;"
  "Jd/TDfPhoU3RMCIZ^VW[ceX(=+#H%Bi$6a3pAck=H(5^#_bS/.>0;hLi4@m/cHPQ#K>Jbupu]?0$[pc)ux*#,Y6e'/"
  "siIfL(9Fl]'rB#$Y)w<1&urnLEh?xOv(GW%_xol8Wt6Z.RT)*4"
  ",5^+4$-0@#OmUS<alsH<Im[E=u9GD#PEMmLDLT_-&*5:2uIJL(YwH>#fjHd)dNYQ#AuaLpM8D6r)DRVH$ZA8.X`.]Xlj6&"
  "mGnP&#U(I]-)UJ_&TvvdF@(+F3E^R[uA$E99D[1^#l6`T."
  "JmV]+%*6x1^p^#$?.)hh4_-P<:2l'MW_Qu>XZDxOtw_+;*Jobrc@Y-?UN&##:o;dOxwSfLwe(B#n&X)bYpNC?Hbc3OGaN%"
  "tQ9Z&#,JDU2Kd^5/O.[0#.F278GKgv->;gF4i3F,%St]:/"
  "$$4^SFn^&SHFvoCL::5D`kqjX18tnXPxO%:LGT<L@x:hG>orEIB(&FI_V###Sj'u$LHF:.%<b,36>PjLT%v4S8C^wJnpCW8&"
  "<pg#r7o>D8=Lfu6i<>9D;1@-O^we-4[%RN-&pu,.xHs$"
  "b+WT/l*5[$=.e8.Oe4D#v/A`#wQiB>GihDRF$6^S%NUA,V:f_ulA2U3h*nY8_==;6A2.XM/*/U/"
  "cY18I33-NCP_ri0$K=p&i79'#g<3:.26;hL6+B.*dWcf%bf@`=3osNW'Q4@E]ctQ:"
  ";D;M#Y?PZuv(,YuV3$sCJSI]8'Tq)0jq]&v5$4]#NS/"
  "N-q43j$4fK+*=+pv-c,kL)9'04M`xnf3de_F*a*OtHUBM02a-#uJt&jc;0a5l2bsnh<'U'`%?.Ig4*9vK1*U)#Cmd_;8I&"
  "94("
  ":d$eOUSIkM``Z##Aau)MXjd##m66g)P)&=.7872fciVVH7jjp#l6fY-3$7kOtf'F.NK&F.%8hd4eR0N(,['u$]p*P(^m]6:)"
  "6cQjq;Lfu1r61<d<TiuNE-aIZ0&vLUG-##75YY#9Woc4"
  "DmV]+)bM8.KMvD^28YIk3C9.qk6?xOlEP_/"
  "UM###m5v>RsO+.)+K7X1@ng#UP.U2?n`shPI[5R3g1Xrdf8cP&AW&8RR_9.6XAJwBTcWW/>G_;.2cg/"
  ")slEb7Jp'&=FUa(BKbXv]T@7tt"
  "Y.<D#a/YY#=m$8#.+35&@#j]+VswV%&/"
  "vN(nkLGDf^(dlI=cHdOKaV-Xr0uuE?fuG?j.N:<TQD*c+?u%[x2D#_H7g)`0eX--QFeuaEH&Mh'Heu,[Oul`MVaue*J3M<l,"
  "*vA=6_#[Oc##"
  ")N/i)2-k-$F4-MI?D.DjN_GU9A,KwK,&U._*S4XS@.=F3+h#I<R)n<SPL?>#[vFiTKVAF7bqY)4B-k-$jJ/F7Kf/"
  "b#2u`-6Va.cr#<of:;SK-Q:]TU/-[7j6ou&dHo#)cuh.A=#5k4c4"
  "I`v+VDH&v#[-wX-=:O`#Z[2359I<B/"
  "9lrO#*NU5M?@CF*w>&Vo:ZdS@$SPrL8W@M9K#'Dj'kc`*D1$##K.rv-@b>d3KjE.3-[w9.nLMs-Z3%.M76/"
  "M)k_+D#8p+C7?3;Q0-5lZ%nCrw@"
  "^t1q9q`Ee5DdLu7u6gEFQEt]@ESY@@]D%I+dc.60-,g9Mff4JC13?)*1B52':i###9x^32*rE<%G-3l(2b;78:q;Q/"
  ";]RHJwa`h;'q(J<e5HD<8dxF#$NELlcti'>uR5xt>jD=82Ng_B"
  "='J,3KMmre=x2g)-9TaldPSF4CM%+<6q;Q/FiLt'3;A>.tHr'HpRne>(PiK#XI4?%-un/"
  "X;Ohh;$=6ANbG.;6Oi_oofn#B#5thTr;lC,3C<1T%D59f37Lb9<&'_I;Kdc&Je9#i<36-)<"
  "$?qf(KQrR1H<HxN)T,%C?m`X8r*94M5/F'MFMa$#argo.tS5)%@LG<q2k;W-1007/"
  "vBo8%@w=5&FE0Y&_;Q^I.bGt'JawWJ5$1p9a#N%?)]AImX=Wr:Oi.x&F(0qL,U-##U,>>#2Vo5#"
  "DxS,MZrte)XxAk$8,B+4TxwJ*P)W/)5r/"
  "tB_[?1<o@dfCqnR3:]?iG#=XIq98[rB8Y5>##KuhZ#08<)#*^Q(#CkP]44Y6MMEJ^I*u9_=%x%'f).5lk/"
  "lm?d)%aE.3[hIW-Kb.@@?Pq;."
  "U7-5/BN_V%V_D.3>OH22/o?xS6G)b5T,X8.KZ/"
  "51k)ao_9EwDoKPB`=,vEv-Od+D#3LG(7c=Rx6UR<&-.ux-<+Tf)4'SYq0'2sN*=FT(4N:LbGt,kE4(x0P:9B1^#7P6+"
  "8fXsU8NKGj0"
  "56YY#+%&5#G$(,)t(6W-pxe9MfFIJ3xTvI>7=n;JcMfF#5er=B$t1&+rF&C@1c?=..&w4A0.n]cTp@3td'?e6Yax9.<50("
  "miVOO<c=M`+93GA#%T9^#+$Gb+Vtp<1L2Puu-e1$#)1<u."
  "CXI%#<im92a5E.3wkh8.I>+P(-eB:%@f)T/"
  "j9.l+6Xi@,01XH?afmu-BOQ87xxACubcF8.StqI-h,2w.$),##56YY#vG[uL[o,>%xYS$9x<_=%9;Jn7nhdYFGp-Hux23>"
  "Ybeae]P@f<L"
  "M$Q&#'U%4:D^OAYk(4O+O),##5?uu#bUv;#]M.Q->^BK-E%Ok'n.rv-Lp5e5`>u(72h`9Jhc*x7qg)x770HD<S9&UDKt$&"
  "84pK3C)u1&+iY6*?um+%NRu.s$Tdi2D)hp_-QC[@9X$&.6"
  "(Ct(3a6c.qhuTT&6]###3d(99OKv)4FJ`20a&SF4k`pZJ3)n-$)I,eO6C+V;a=R'JoP3bI&TUCBH5A<B5f4JCP87)*vn.g)"
  "6-O-3vbLs-:o0N(.d1@en?vg),/]>2>n1<_UiC#e3s#s:"
  "^RZoRpEm=OE`,r#TfYvA`6V$7[?`*#HX.H3[38/1&+a/)UOU-Q)-/J3uUB+*8v19/aqMs-l.ad%vu/+*KD,G4?U^:/"
  "lBRq1IWa@,%fHE5YgC?K)#DG5P4W?#5Q(#@st%$3BM4W6g,EtS"
  "rK2YO)KK(BTbH;@4LLfLVfp.C7k>gDoR72'F:Kv-o1bHZpv%J3vW9L4mj@G$A#p;@'D#Z,]fA,op#h8C[5RgLU]/"
  ";6Atl1g^ra?Tnd`.3fiCm91,BFcMaHX/G0qL;C2(e#f[En2c`>qA"
  "vtr3a4`cb#=c't/"
  ",8_K#8G8e4<oW=.Iblw5w(KY8<21[6>Q,s.,*,##-FvV#=*S-#^rgo.NlOjLt<x9.IvsI3<;nQW@(FF3B+GPA_A1i)mH-1<"
  "e(-w.IeVH*M;l:.b^jiMk>v_jDt7_8"
  "E=$`sTP>]kPv@_8`]d8/"
  "X$nO(^%*<-N,tI3X?\?YYx-9rBv0i,=#JdXAEuCH#MvO0Jrccsuw*LS-4VY8.>e^:#KLXg1`hqf?NZXR#xEqJ#R43jL9@c("
  "N.]I`a:9f?RxDgo%EkefGERE5<"
  "=w4lEp74R34P^fC;+=JLNckG<A,<.6vp;b7L4]9VXw2$#9f2T/V9>V/--/J3rE'/"
  "BEV$<^F#H:MQL,E^n@`)^(+u_.3lL?#0[qlLl]3r7(I1a4O0AhG78Ls-bBIF49>]L(5Q``QZtJW*"
  "V4xcOuarx5%C*'/VN3`:0,vNFQP,lLra;xLCTDs%[x2D#ZH7g)&0fX-rb[[u((1fu$L7[uQ>,5AEFgCW;W)/"
  "5pwq+;E<9>>1Zwu,L]&+*xL0+*neP)4T,RI%]M(a4c4)=-BWKo/6V(]6"
  "heu-)L>&s6CIql:pp,,2C;g/=Zd?m@7B;@./=Uu2x/"
  "8J=tcBiL]S,*vaukm#$RF?.;de;u*9PG-A.PG-O:PG-[i+c-4'$CJ]#G:.Xxk_._;W.3ln7Y-rmK.H+Iw1Mk2)c+(*pF>"
  "1Hk81"
  "7hTm00/"
  "ZkLik=x@5;R-HEh](#)c<T#F5i$#`im;%;jE.3+2pb40<Tv-5jIjUXJ6[-0IVO+^Yd<.L+aW'K.Ux5pm*D5(tgv$wh[^08F."
  "%#8LI[#e':Q9/dDh)N0D.3u3Cx$M3H)4^Mc)4"
  "9EsI3;k0T%V0&;QB(_B5nLCm^1sH#>0R(duDF6<.=JwA@&*P?#:ui5:vRhw85b9h;fHDk1C46uBTaCnLfcZY#I6kP&lJb]F^"
  "r/eZUt7<-Iws7%p#BA,:<4#-_Kj],<W:#$=)cB,3RW-Z"
  "[Ik%XfrNq0f^A8%OXvr-tf&9$cYghM@m;A+J($p.@3w;%Z.JfL*o6F<@/"
  "_#$cCAH<PA=mBlQ@_<Fv0B#?7GCG1o[H7C,^6E>a1,N8MdF7FUk?KK*$xK0Ti+M#e6b<K]1a4v7g(8[UQOL"
  "ksUsNlJ*e/k.u2UZM&j:)k#^,L(hU/"
  "TbCE4dbL+*.G>c4i7Ls-q=;+R)?F)+]3Me3S<3D+xx7T&16f>6P[`m26U=F37N;o&I]eI25KmV%><Zp0gm8NMlX/"
  "%#UfJF-Hb2^%7IiAOC-rx7"
  "gIe[BO`qDY^_6##3->>#kYi,#8Q,b<<=mg)8+U/)dL]d<dn`8AmZ[$=vG%krJ1$##F(rG3XVlL#Dt3Q/"
  "S3.Q1x4E_*o`6h8Nh7OGD7l-6Uu._JHVTGDRHoM(OoxA#g&@e6.VFLjrccrH"
  "p=i5/UqKmh#EM/8)fB#$x/mS8v$Ag)i=(A9dJP$Pl3%#8/"
  "79I?.gq&-0F5gLToxw#5$CW$Q*nO(hK^:%NQ[L<)?8TT#Q^W$Q`qr$5nOJ(%)_G3$Mv`4g2D_/h0dTrAIpoMW>Nq-Q'E_/"
  "O6D9rT(no%d-LhLWK.IM0sX?-_`o_%S,N&#E:C?$:E-)*JOe'&h^_c)Q6)^#CY9hLS#RaPGm?xOKxeM.3SSiB;UY2:mYL'J,"
  "v0X:F$nO(H3I*.Yrq:8qtkmB`^SA?6c:;=9x-W-d]6^Z"
  "^X6##DTOVH$dN%t`Ph&(YO%I3pd+#>7>65&O8[`*o,U:.lH3Q/"
  "mjt9..u]erod=X--1sJs]195;LAb2(2+Wf4LW->%q-MP8En2aJGt)EJM:+F?&:E0kH8Q)M3>BwU[W987lL7T.*]ghM"
  "r+TV-XXs-?5TsE[N*jG[lNJ;Q<LI#8V2N:K(PcD8iuHW&pA#OMIdbjL^ho,8^B7PbwgX,O*srjXn%VYdvFm<-TXXR-7:I*."
  "RLSsRZtR_#HjE.3wkh8.G>_;Q3%wI8f%h=qd@HH4RCZY#"
  "D2Hp.=u./(036FuQS5J*N5wF#qwf_o1t?`$p])&NLsB#:;5^+4@6;hLK?e8/"
  "@v2<%ZfHSL)RQC?cobG#@3MRo1axU9C^t@=>#CWJfPtJ-mEtJ-7A4vLrKYhN(Hf(W@]I&=I)1#?oA(6/"
  "sTot#wXVmLY'g%#I<qC-Uu'A(WJ6/MPu?<QSP'%8M'C#$95Dm/"
  "o<c`*j*io.L<6'.jK^:%ufLn<;&-semZ[$=w^U^#M7GCGD[1).ev%HWZ3t1)v:&VSI*8G=M^C_*Cgw]/3gb.hL351#"
  "+x-;n0ctS/r5fW8`v<^/-Ln03d7gq]TN/"
  "a=TnwSgMqCH-cs$*.u+cIWODk%$xmaq7c=rA5nq4&:fJU&T,E)E#^e,*(IG:;$A5l;-/"
  "wre.p&U'#;nx_9+w;Q1u3gK8T[m>Usq$Gi@*Gn/"
  "MKSX#4tp:#piTK-aGYT+jK^:%RE#'=:GD9J4':p9N#:io?I$l`cXBMBacP29b0nwBvP<A+F3Xs-LaM^>DO)B42m&f)?S>"
  "c44C4D#RE<$8nZAq'BF9aIFBc[&8Y/8%/6I_*R5YYAXG(qN"
  "),I7:*QY%7D_.*;l2YD4dEQGjVt*Rag4ATa;Z=_AL#`4br]:T.6)n63L=)P-M,jB%4&bo71qu(bS]Nv-QNssDK)Yq7'p&"
  "8oaM:<QY&=0(UG###p4(Djqs]<-^<Sn$(cgquhnBI9(XrS&"
  "XxH,*G;93iPMZT/s4MRo,dQQG*@Es-1O8(M_<$b#%mH7:^xt?0xv`GM%RCX8;I]'/e0O]#xl5U,X(:3iptWB-G/n>'Ce/"
  "A=K(tYdYOho.(b$x-0[1N(MG#G4<)]L(m=]:/>0?L1ow282"
  "m4+c#v-m/<jlf#Re:0aD7?]SoicN99$t1&+%eOa8B0n$$LiA(sIp/"
  "DjAE(,)AbB:^xu[D*eAmf(_3X9.fu]erg^Kq.t#173b>0dkPGn7:]@Y)4[R,gL6J(u$t0A8%^B#l=mQ>eO4u2]9"
  "CBC_*jPQ`-:A`2ivq)M-Wq)M-jEoC9M2'MYvLLOLsf/NQ7RX,8)I>F[B,3F@=-idk2[sM-XW2j(X>s6a_/"
  "3-k]klG-46#=('_(3;>JBt#a;I*.PFJsRU7e+)b&7DtA>6<QosmI8#OU'#"
  "'3V(voxO:$2puB=#@-.kpo[D*/vEFlw.)ioh^e_mZ[Z>#Lf)/"
  "#[5W[%rQnb4Jax9.vkh8.Ygx9.r:F.)4C4D#sbJI<xIg)Gnl4brBx5HDMO+1oX>:K#&^:KA2';f8%dI_Sk[%_Sx$)`H"
  "f:U5%w(%q.:^7tL3gQxTNuf%8.gB#$qA3^#.j>%.J(W;R#[Kp(l:drnW%VZPN*tc'N,>>#3T&##d*<]k9f;9.$Bar-WfLk+"
  "mX+DWOY>>G.D###i$A+%VbCE4dCg/t[^B2'oO+01>q3]#"
  "LAN-$;BP##s$:`$I$ZTMpG&$&gK?D*I4[]=.Y*,)cg=g$Xk[<-*tnv(689588FCB#]-I>#Hd@hF3:4D#4<GvC7>Lk+"
  "qtvQOwEDGD]j)l+cOf(Wdw(^G0x0wgDE*jL0R6J*].B+*2n6&5"
  "4g]'5N:%],3q'j180X@,6JOA+RD.m-=./R3_vXYG;(/R3)gB.*Ynn8%3k#;/"
  "ni(?-2=(41#';$-od921s_rK*+DL1MYG;pLJ=Qu#6`?iL*k+_-37_F*?mZv$<7@W$)KsI3;O'>.-P39/"
  "rl/"
  "H#%w5q']`M#G@smf(nUCq6i,<Poa@+P;_Q,p2.vi$H_D9At'0=F5=IRlL?_4D<lAp1Ta.,C#:%xC#txkQ#D-2*#?_&T."
  "S3Zr#?SO$%o31H2LrUv-]WD.3&^ncHg(io@X;*/1g$ZSN"
  "WmpoN3=;Eh9D)t%DIH[/"
  "2r^N2oo'f3BC@30p;g(aF2>>#d9%##UBQwBbr###)t_<L>M>c4a:M3a&t`L)=C[s$.lBJCZ$1O;3;nX7>8Fv>$f4OH5kh="
  "BZ$Ni<WZMo&[JJl1W(&;BtbR_+"
  "pcP9`g#sx+K9c1pA2sV.JJWv-2M0]?50%:1gJ8f3=dMX%sjE;$fun1*CSUJ5^skQLrS6c#V=j`?)B7p0YmVE#dSn*AG5_2)("
  "OqG=HtM<9:]l@?nA=g3l+%##=bnwu,#4]#=PTK)6?J1F"
  "-@CR#P[7t#49dY8K)pD#$m(G#;aTg-5fnQWfMkV-btEYfh>(u$T(Z:A[85L4eTB/`dlL_I+3-p;<;:/"
  "=2kBA#n*&X#'g9R`Cp`G5&VQ<:tM'nL*jn9D%4=#v4.Ro#7Nr5'2LdH#[%Sl#"
  "Fx?+`l7@3D,Av]PfuE-Z6Y18.VB')3w(J1(pxW/)iYW0tK&xf3Hf+)4fUNmLmI+j=D$-+-Aaj5AdZs]Ae$%_H4k]P/"
  "0gNcutE@f>Cn?@579=g;A;v(?=f_^Himw=9k:''#H%M$#2xAgL"
  "AE:sL0=`T.)AP##^4xU.,Mc##VA`T.PvK'#YsG<-N2:W.5rC$#:g`=-,fG<-?B`T.<.`$#LB`T.=xL$#]B`T.'C,+#q#"
  "XN0Lt*A#X5>##_RFgLb<tW#%A`T.0r_Z#k@`T.54.[#u@`T."
  "'0Vc#)sG<-N2:W.D'F]#4g`=-,fG<-FB`T.NK'^#aB`T.M3X]#+C`T.w(20$*CfT%;$U`34cWdF>M_oD2<XG-MhW?-=Bnh2)"
  "/=eF%^TSDdZvc<(&QhFLF5p/)/JT%%]w%JnBrTC+^,LF"
  "DZV=B5UOnBUHI31Ct7FHdZvRC:1k(IS7fP9@NXG-PmnUC$NR/;pvM=B5[HKF@][Q/gD/"
  "0FI-@j1885E='DvlEUE?U2wF6fGB0E,31-s]5fBDiL@IMiLg2NI34qLO1pb2_>->hoDRB*g2"
  "73IL2qDfM10LB`]8:vLF0nrQWmJWnD1Zr&0lIrEH)6FVCfo8[5mHiTC$k`9C6P]:C:WI>HeZr`=(@YG<BK3oMAWPkM[]q?-"
  "4,6i2M3FGH,C%12+a^oDT.xr1E87r1#tS22Zm.+#+mk.#"
  "cSq/"
  "#TH4.#HB+.#c:F&#Y#S-#Or:T.0E-(#M)B;-RfG<-9w'w-vZhpLM:SqL9_4rL'T#oLf_4rLge=rLg+m<-6.0_-'N&Y("
  "uCVw0RMw9)i2s.CQe`uGBIcDFK1,XCutY'8s1L`E;cb9D"
  "xLh%FKAu?B_qHe-4^,R<cj0A=]ZYMC>n)vH34=2CxLfP9e#J>Hsm;,<or3)Fa'(?-;0s+;Eje]Gq/"
  "C5BF(X>-EEDX1^Xk>--Ncq2Tk`'/YCrKGra4XCx'AVH#Vp]G:P26M?wXrL$*8qL"
  "dJhkL%>UkL]$[lLmk?iMQE[]-;Rm--Z/"
  ";D3,gYc20GLe$nkv;-oi)M-6qJ7..T3rL<V?LME>UkL=_KC-Lv%?O8op*-2Zi+M@u^%83STp9K/"
  "w+#EY`=-iqmq&H-p92&r%;HQMw1BRDO-Q"
  "a,ke-9e/F%8<_w')uW9Ve2s.CoLcYH#[B2CDt^>-^vUJDJo>a=dY9G;2djG<Cmkw0wmCW/"
  "C2oiLpU5.#:8K21N(rxp#r]JD4CH>HCn/^5+v4L#ooi34aLf?KKDWq)<u`f1s@VW&:e=rL"
  "x5JqL4NpnLJU-+#1/dG%RkF6#>E^2#,7>U)A0]'/"
  "g3@##,AP##0Mc##4Yu##8f1$#<rC$#@(V$#D4i$#H@%%#LL7%#PXI%#Te[%#Xqn%#]'+&#8wdiL0FQ&#iKb&#mWt&#qd0'#"
  "upB'#"
  "#'U'#'3h'#*qN+.]8^kLS8,H37Jr%4;cR]4?%4>5C=ku5GUKV6Kn,87O0do7SHDP8Wa%29>8*aj^+^*#b7p*#fC,+#jO>+#"
  "n[P+#rhc+#vtu+#$+2,#(7D,#,CV,#0Oi,#4[%-#8h7-#"
  "`F31#?x&2#E7I8#D?S5#QB[8#Q0@8#i[*9#iOn8#X7o-#sb39#OE]5#b/k9##+b9#KN=.#MTF.#RZO.#Zst.#_/:/#c5C/"
  "#gG_/#lY$0#n`-0#sf60#wrH0#%/e0#S45##+C0:#4^+6#"
  "=)lQ#m#jW#.Ml>#2Y(?#6f:?#:rL?#G$T6&-%S+H?fV.GoISZG)k%UC5EsXB0X66JCfRr1S:X7/"
  "o)6[&DK3kN;x?DIIdx5'-KFVCJa]p&6=ofGU,Tp&GM#mN35mvGOA,o*.=LVCKg/lN"
  "#R:nDE>glNP*7oD5vI&#xhBB#$,P:vkiu'&AtjYd%4bkLn^Grd`F6LMOm;'UmmRfL0ecgLajA%#qr[fLS:-##rBg;->_Y-"
  "M8:>GMUIGHM,XPgLGV`'#gwCEHDTl##CwlhL&#TfLeZ7DE"
  "<?*:)tx*GMD$JY-_GL_&PD>>#ZK'@'vW%##5d53#J`hR#SvTB#BDaD#Z7#F#HQ^q#I_e[#>eGj#%dFm#jT^q#L#js#rIuu#"
  "Gk*x#*j)%$_h(($Q)L+$,@p.$q>o1$*_mL-tHKC-OA=?/"
  "rd0'#%^jjLH@6##OMYS.XP?(#O17`%^cR]4d;2>5i)po%Xj@M9#+v.:)A./"
  "(jxp(<23O`<AX')*pHoa45b9>5B9UY5kn8@6SrBJ:r,LV?imgr?i#HS@9ehB#GZpRnXFLS.;x,F.&'ru5"
  "RPDX(-#gl8+hcP9,q(m9k0C2:qZHj:I47A=wG4&>w`K>?4P$Z?u9?_8(I,8@*@Xw96Nv9)%(AJ1)d5a4<QxKG<kNq;<R7X:"
  "DC`3Fv804F5^'v#/Vacse1]9Mj7c9D<Y2eH'/hQj*>'XU"
  "Ac<X(MGHJ16>IwK=FDM9vv`i9ma%/"
  ":tjQN:9)^f:sMT`<2j8)=uAxD=(,Q]=wG4&>>iCB>1YMY>qx-;?.8hY?+5-v?m]c;@Mr(kkr0co@a`pP'T5x`kB]=%tSbD,"
  "3in=p88xW'AXuW'A"
  "XuW'AoYBJ:C#8j:WF`Kl*inx=]*4>><;h3=2;72'KVi-QE[Q`k,[Q`k%r=Ji.+2>muwH,3n,-a+h3)/"
  "`-qolpL^^'J&K$)3CE+d3V8lD4kt)kkaf*XL]Y*XL]Y*XL]Y*XLfV(kkY2(kk"
  "XAq%=DOY3OfV(kkiqqKP6WvE@6WvE@_xiu>6(9_Aa.JV?Q'gr?$&H;@SgkV@a>1s@Tg@?$W^LxXU`Fe-v5Ks-u$ffLoVZ)M:"
  "97;#3#`AMA`:%Mc&h(M`pp_MDuY<-i0;t-.7+gL54X<#"
  "@IKC-XP;e.T=Z;#&fj/"
  "1cIm;#sH5+#tNi,#4Y5<-ns:P-x:cG-s*NM-GX3B-2Lx>-&A;=-)N#<-3S]F-Spj3MP-b^M(4pfL=#5$MC(i:#kUA(MCYL["
  "M*;.&MX^T_MRnx#MK_e&MwZ,oL"
  "*G.$v'lv9/><5'vG[B)Nu(h(M/"
  "Lt'M[x_%MD@@;#;fr=-)rY<->wWB-Cnls-%1xfLiRm`M404%vF6)=-0_W#.M+ofLk&h(M^-F'MCeB(Miv#`M*e>wNA2N*Mu>"
  "6)MT(i%Mi8H`Mx3o,8"
  "Ud'B#g+BP8'@AaFum].#UgUx$0BAqDBG$T.-/5##$;ClLS?TG2&),##Rww%######$####WDK[k^=91#";
#endif

static void SetupUI(vtkDearImGuiInjector* overlay)
{
  vtkNew<vtkCallbackCommand> uiSetup;
  auto uiSetupFunction =
    [](vtkObject* caller, long unsigned int vtkNotUsed(eventId), void* clientData, void* callData)
  {
    vtkDearImGuiInjector* overlay_ = reinterpret_cast<vtkDearImGuiInjector*>(caller);
    if (!callData)
    {
      return;
    }
    bool imguiInitStatus = *(reinterpret_cast<bool*>(callData));
    if (imguiInitStatus)
    {
      auto io = ImGui::GetIO();
#ifndef ADOBE_IMGUI_SPECTRUM
      io.Fonts->AddFontFromMemoryCompressedBase85TTF(Karla_Regular_compressed_data_base85, 16);
      io.Fonts->AddFontDefault();
#else
      // get framebuffer size
      ImGui::Spectrum::LoadFont(32.0f);
      ImGui::Spectrum::StyleColorsSpectrum();
#endif
      auto& style = ImGui::GetStyle();
      style.ChildRounding = 8;
      style.FrameRounding = 8;
      style.GrabRounding = 8;
      style.PopupRounding = 8;
      style.ScrollbarRounding = 8;
      style.TabRounding = 8;
      style.WindowRounding = 8;
      style.FrameBorderSize = 1.f;
    }
  };
  uiSetup->SetCallback(uiSetupFunction);
  overlay->AddObserver(vtkDearImGuiInjector::ImGuiSetupEvent, uiSetup);
}

static void DrawUI(vtkDearImGuiInjector* overlay)
{
  vtkNew<vtkCallbackCommand> uiDraw;
  auto uiDrawFunction = [](vtkObject* caller, long unsigned int vtkNotUsed(eventId),
                          void* clientData, void* vtkNotUsed(callData))
  {
    vtkDearImGuiInjector* overlay_ = reinterpret_cast<vtkDearImGuiInjector*>(caller);
    
    static bool windowIsOpen = true; 

  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("Tools"))
    {
      ImGui::MenuItem("VTK Info", NULL, &windowIsOpen);
      ImGui::EndMenu();
    }
  }

    ImGui::SetNextWindowBgAlpha(0.5);
    ImGui::SetNextWindowPos(ImVec2(5, 25), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(450, 550), ImGuiCond_Once);
    if(windowIsOpen) {
      ImGui::Begin("VTK", &windowIsOpen);
      if (ImGui::CollapsingHeader("vtkRenderWindow", ImGuiTreeNodeFlags_DefaultOpen))
      {
        auto rw = overlay_->Interactor->GetRenderWindow();
        ImGui::Text("MTime: %ld", rw->GetMTime());
        ImGui::Text("Name: %s", rw->GetClassName());
        if (ImGui::TreeNode("Capabilities"))
        {
          ImGui::TextWrapped("OpenGL: %s", rw->ReportCapabilities());
          ImGui::TreePop();
        }
      }
      if (ImGui::CollapsingHeader("vtkRenderWindowInteractor", ImGuiTreeNodeFlags_DefaultOpen))
      {
        auto& iren = overlay_->Interactor;
        ImGui::Text("MTime: %ld", iren->GetMTime());
        ImGui::Text("Name: %s", iren->GetClassName());
        if (ImGui::TreeNode("Style"))
        {
          auto styleBase = iren->GetInteractorStyle();
          vtkInteractorObserver* iStyle = nullptr;
          if (styleBase->IsA("vtkInteractorStyleSwitchBase"))
          {
            iStyle = vtkInteractorStyleSwitch::SafeDownCast(styleBase)->GetCurrentStyle();
          }
          else
          {
            iStyle = styleBase;
          }
          ImGui::Text("MTime: %ld", iStyle->GetMTime());
          ImGui::Text("Name: %s", iStyle->GetClassName());
          ImGui::TreePop();
        }
        if (ImGui::TreeNode("Mouse"))
        {
          int* xy = iren->GetEventPosition();
          ImGui::Text("X: %d", xy[0]);
          ImGui::Text("Y: %d", xy[1]);
          ImGui::TreePop();
        }
        if (ImGui::TreeNode("Keyboard"))
        {
          ImGui::Text("KeySym: %s", iren->GetKeySym());
          ImGui::SameLine();
          HelpMarker("VTK does not flush KeySym per frame.");
          ImGui::Text("KeyCode: %c", iren->GetKeyCode());
          ImGui::Text("Mods: %s %s %s", (iren->GetAltKey() ? "ALT" : " "),
            (iren->GetControlKey() ? "CTRL" : " "), (iren->GetShiftKey() ? "SHIFT" : " "));
          ImGui::TreePop();
        }
      }
      ImGui::End();
    }// if (windowIsOpen)
  };
  uiDraw->SetCallback(uiDrawFunction);
  overlay->AddObserver(vtkDearImGuiInjector::ImGuiDrawEvent, uiDraw);
}

static void HelpMarker(const char* desc)
{
  ImGui::TextDisabled("(?)");
  if (ImGui::IsItemHovered())
  {
    ImGui::BeginTooltip();
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(desc);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}
