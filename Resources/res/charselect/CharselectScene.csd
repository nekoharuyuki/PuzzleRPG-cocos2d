<GameFile>
  <PropertyGroup Name="CharselectScene" Type="Scene" ID="1c049daa-f7f3-4146-891a-74de4f50b3a4" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="2" Speed="1.0000">
        <Timeline ActionTag="308958992" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
          <BoolFrame FrameIndex="1" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="1644708471" Property="Position">
          <PointFrame FrameIndex="0" X="403.0001" Y="291.0002">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1644708471" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="1" Tween="False" Value="True" />
          <BoolFrame FrameIndex="2" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="1644708471" Property="Alpha">
          <IntFrame FrameIndex="0" Value="250">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-2110163777" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="2" Tween="False" Value="True" />
        </Timeline>
      </Animation>
      <ObjectData Name="Scene" ctype="GameNodeObjectData">
        <Size X="800.0000" Y="600.0000" />
        <Children>
          <AbstractNodeData Name="bg" ActionTag="55817606" Tag="60" IconVisible="False" ctype="SpriteObjectData">
            <Size X="800.0000" Y="600.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="400.0000" Y="300.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="Normal" Path="asset/shared/bg.png" Plist="" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="title_princessselect" ActionTag="1022191821" Tag="61" IconVisible="False" RightMargin="470.0000" BottomMargin="523.0000" ctype="SpriteObjectData">
            <Size X="330.0000" Y="77.0000" />
            <AnchorPoint ScaleY="1.0000" />
            <Position Y="600.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition Y="1.0000" />
            <PreSize X="0.4125" Y="0.1283" />
            <FileData Type="Normal" Path="asset/charselect/title_princessselect.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="popup_1" ActionTag="308958992" Tag="62" IconVisible="False" LeftMargin="144.5003" RightMargin="138.4997" TopMargin="130.4999" BottomMargin="112.5001" ctype="SpriteObjectData">
            <Size X="517.0000" Y="357.0000" />
            <Children>
              <AbstractNodeData Name="char1_btn" ActionTag="-1706714847" Tag="1006" IconVisible="False" LeftMargin="41.0000" RightMargin="376.0000" TopMargin="135.5000" BottomMargin="121.5000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="70" Scale9Height="78" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="ButtonObjectData">
                <Size X="100.0000" Y="100.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="91.0000" Y="171.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.1760" Y="0.4804" />
                <PreSize X="0.1934" Y="0.2801" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Normal" Path="asset/char/icon_chara_b_1.png" Plist="" />
                <PressedFileData Type="Normal" Path="asset/char/icon_chara_b_1.png" Plist="" />
                <NormalFileData Type="Normal" Path="asset/char/icon_chara_b_1.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="char2_btn" ActionTag="-1983845064" Tag="1007" IconVisible="False" LeftMargin="205.9999" RightMargin="211.0001" TopMargin="135.5000" BottomMargin="121.5000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="70" Scale9Height="78" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="ButtonObjectData">
                <Size X="100.0000" Y="100.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="255.9999" Y="171.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4952" Y="0.4804" />
                <PreSize X="0.1934" Y="0.2801" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Normal" Path="asset/char/icon_chara_b_2.png" Plist="" />
                <PressedFileData Type="Normal" Path="asset/char/icon_chara_b_2.png" Plist="" />
                <NormalFileData Type="Normal" Path="asset/char/icon_chara_b_2.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="char3_btn" ActionTag="-1062706575" Tag="1008" IconVisible="False" LeftMargin="370.9999" RightMargin="46.0001" TopMargin="135.5000" BottomMargin="121.5000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="70" Scale9Height="78" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="ButtonObjectData">
                <Size X="100.0000" Y="100.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="420.9999" Y="171.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.8143" Y="0.4804" />
                <PreSize X="0.1934" Y="0.2801" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Normal" Path="asset/char/icon_chara_b_3.png" Plist="" />
                <PressedFileData Type="Normal" Path="asset/char/icon_chara_b_3.png" Plist="" />
                <NormalFileData Type="Normal" Path="asset/char/icon_chara_b_3.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="403.0003" Y="291.0001" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5038" Y="0.4850" />
            <PreSize X="0.6463" Y="0.5950" />
            <FileData Type="Normal" Path="asset/charselect/popup_princessselect_1.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="popup_2" ActionTag="1644708471" VisibleForFrame="False" Alpha="250" Tag="63" IconVisible="False" LeftMargin="144.5001" RightMargin="138.4999" TopMargin="130.4998" BottomMargin="112.5002" ctype="SpriteObjectData">
            <Size X="517.0000" Y="357.0000" />
            <Children>
              <AbstractNodeData Name="yes_btn" ActionTag="-1919112154" Tag="73" IconVisible="False" LeftMargin="39.2396" RightMargin="329.7604" TopMargin="386.3157" BottomMargin="-81.3157" TouchEnable="True" FontSize="14" LeftEage="48" RightEage="48" TopEage="17" BottomEage="17" Scale9OriginX="48" Scale9OriginY="17" Scale9Width="52" Scale9Height="18" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="ButtonObjectData">
                <Size X="148.0000" Y="52.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="113.2396" Y="-55.3157" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.2190" Y="-0.1549" />
                <PreSize X="0.2863" Y="0.1457" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="asset/Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Normal" Path="asset/charselect/btn_yes_on.png" Plist="" />
                <NormalFileData Type="Normal" Path="asset/charselect/btn_yes.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="back_btn" ActionTag="-749322853" Tag="69" IconVisible="False" LeftMargin="328.5226" RightMargin="40.4774" TopMargin="385.5000" BottomMargin="-80.5000" TouchEnable="True" FontSize="14" LeftEage="48" RightEage="48" TopEage="17" BottomEage="17" Scale9OriginX="48" Scale9OriginY="17" Scale9Width="52" Scale9Height="18" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="ButtonObjectData">
                <Size X="148.0000" Y="52.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="402.5226" Y="-54.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7786" Y="-0.1527" />
                <PreSize X="0.2863" Y="0.1457" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="asset/Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Normal" Path="asset/charselect/btn_back_on.png" Plist="" />
                <NormalFileData Type="Normal" Path="asset/charselect/btn_back.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="AttributeNode" ActionTag="-1747103687" Tag="1010" IconVisible="True" LeftMargin="317.7855" RightMargin="199.2145" TopMargin="95.0921" BottomMargin="261.9079" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="317.7855" Y="261.9079" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.6147" Y="0.7336" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="NameText" ActionTag="792179082" Tag="1011" IconVisible="False" LeftMargin="353.5000" RightMargin="49.5000" TopMargin="83.5000" BottomMargin="244.5000" FontSize="25" LabelText="Text Label" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="TextObjectData">
                <Size X="114.0000" Y="29.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="353.5000" Y="259.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.6838" Y="0.7255" />
                <PreSize X="0.2205" Y="0.0812" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="LevelText" ActionTag="54091902" Tag="1012" IconVisible="False" LeftMargin="358.5000" RightMargin="125.5000" TopMargin="129.5000" BottomMargin="204.5000" FontSize="20" LabelText="Lv1" HorizontalAlignmentType="HT_Center" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="TextObjectData">
                <Size X="33.0000" Y="23.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="375.0000" Y="216.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7253" Y="0.6050" />
                <PreSize X="0.0638" Y="0.0644" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="AtkText" ActionTag="-698749409" Tag="1013" IconVisible="False" LeftMargin="409.5000" RightMargin="84.5000" TopMargin="164.5000" BottomMargin="169.5000" FontSize="20" LabelText="40" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="TextObjectData">
                <Size X="23.0000" Y="23.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="409.5000" Y="181.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7921" Y="0.5070" />
                <PreSize X="0.0445" Y="0.0644" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="SkillText" ActionTag="1055300435" Tag="1014" IconVisible="False" LeftMargin="306.5000" RightMargin="118.5000" TopMargin="230.5000" BottomMargin="103.5000" FontSize="20" LabelText="Text Label" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="TextObjectData">
                <Size X="92.0000" Y="23.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="306.5000" Y="115.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5928" Y="0.3221" />
                <PreSize X="0.1779" Y="0.0644" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="chara_princessselect" ActionTag="707790892" Tag="1015" IconVisible="True" LeftMargin="140.5000" RightMargin="376.5000" TopMargin="192.5000" BottomMargin="164.5000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="140.5000" Y="164.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.2718" Y="0.4608" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="403.0001" Y="291.0002" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5038" Y="0.4850" />
            <PreSize X="0.6463" Y="0.5950" />
            <FileData Type="Normal" Path="asset/charselect/popup_princessselect_2.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="popup_3" ActionTag="-2110163777" VisibleForFrame="False" Tag="72" IconVisible="False" LeftMargin="99.0000" RightMargin="99.0000" TopMargin="95.0011" BottomMargin="391.9989" ctype="SpriteObjectData">
            <Size X="602.0000" Y="113.0000" />
            <Children>
              <AbstractNodeData Name="start_btn" ActionTag="1807002627" Tag="68" IconVisible="False" LeftMargin="165.9984" RightMargin="199.0016" TopMargin="409.5000" BottomMargin="-348.5000" TouchEnable="True" FontSize="14" LeftEage="78" RightEage="78" TopEage="17" BottomEage="17" Scale9OriginX="78" Scale9OriginY="17" Scale9Width="81" Scale9Height="18" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="ButtonObjectData">
                <Size X="237.0000" Y="52.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="284.4984" Y="-322.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4726" Y="-2.8540" />
                <PreSize X="0.3937" Y="0.4602" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="asset/Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Normal" Path="asset/charselect/btn_adventure_on.png" Plist="" />
                <NormalFileData Type="Normal" Path="asset/charselect/btn_adventure.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="chara_princessselect" ActionTag="-1470185440" Tag="1016" IconVisible="True" LeftMargin="290.0000" RightMargin="312.0000" TopMargin="239.0000" BottomMargin="-126.0000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="290.0000" Y="-126.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4817" Y="-1.1150" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="NameText" ActionTag="1886562465" Tag="1017" IconVisible="False" LeftMargin="89.0000" RightMargin="376.0000" TopMargin="19.0001" BottomMargin="59.9999" FontSize="30" LabelText="Text Label" OutlineSize="0" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ctype="TextObjectData">
                <Size X="137.0000" Y="34.0000" />
                <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                <Position X="226.0000" Y="76.9999" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.3754" Y="0.6814" />
                <PreSize X="0.2276" Y="0.3009" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="IconCharaNode" ActionTag="729557023" Tag="177" IconVisible="True" LeftMargin="89.0753" RightMargin="512.9247" TopMargin="33.4894" BottomMargin="79.5106" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="89.0753" Y="79.5106" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.1480" Y="0.7036" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="400.0000" Y="448.4989" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.7475" />
            <PreSize X="0.7525" Y="0.1883" />
            <FileData Type="Normal" Path="asset/charselect/text_princessselect.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>
